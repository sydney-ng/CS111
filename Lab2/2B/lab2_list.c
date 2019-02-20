#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include <sys/resource.h>
#include <sched.h>
#include "SortedList.h"

long thread_timer[1000]; 
int thread_timer_counter = 0; 
long avg_thread_time = 0; 
int opt_yield = 0; 
int num_threads = 1;
int num_iterations = 1;
SortedListElement_t **original_list;
SortedList_t *linked_l;
SortedList_t **split_list;
struct timespec start_time;
struct timespec end_time;
pthread_mutex_t m_lock = PTHREAD_MUTEX_INITIALIZER;
volatile int s_lock = 0;
int num_total;  
char lockflag_type[5]; 
char yieldopts[4]; 
bool mutex_flag = false; 
bool spinlock_flag = false; 
char print_field_flag[100]; 
int number_of_lists = 1; 
static struct option long_options[] = {
    {"threads", required_argument, 0, 'T' },
    {"iterations", required_argument, 0, 'I' },
    {"yield", required_argument, 0, 'Y' },
    {"sync", required_argument, 0, 'S' },
    {"list", required_argument, 0, 'L' },
    {0, 0, 0, 0}
};

SortedList_t *m_list; 
SortedListElement_t **m_empty_list;
void create_split_list(); 
void *linked_l_handler(void *vargp);
void createList(); 
void printdata();
void format_flags();
void do_computation_insert(int t_ID);  
void  do_computation_lookup_to_delete(int t_ID);
void do_computation_delete(SortedListElement_t *found_element);  
int check_list_len();
long compute_total_time(); 
long compute_average_thread_time (int num_operations_performed); 
void compute_time_difference();
void populate_split_list(); 
void hash_and_insert(int temp_thread_ID);
static size_t fnv1a_hash(const char* cp); 

void hash_and_insert(int temp_thread_ID){
    printf ("here in insert and hash\n");
    int i = 0; 
    int hash_num;
    printf ("we are looking at original_list[%d] \n", temp_thread_ID); 
    printf ("key to hash is %p\n", original_list[temp_thread_ID]); 
    hash_num = fnv1a_hash(original_list[temp_thread_ID]->key);
    printf ("hash num is: %d\n", hash_num); 
    SortedList_insert(split_list[hash_num], original_list[temp_thread_ID]);
}

int naive_hasher(const unsigned char *str)
{
    printf ("HEREEEEEEE IN NAIVE HASHER\n"); 
    int c; 
    int iterator =0;
    int acc = 0; 

    while (iterator < 4){
       int a = str[iterator]; 
       printf ("a as a char is: %s\n", str[iterator]);
       printf ("a as an int is: %d\n", a);
       acc += a;
       iterator++;
    }
    printf ("acc final num is: %d\n", acc); 
    return (acc % number_of_lists);
}

void do_computation_insert(int t_ID) {
    int hash_num;
    printf ("HERE\n"); 
    int i;
    printf ("\n lets check original_list: \n"); 
    for (i= 0; i <3; i++){
        printf ("original_list of %d is:", i); 
        printf ("%s", original_list[i]->key[0]); 
        printf ("%c", original_list[i]->key[1]); 
        printf ("%c", original_list[i]->key[2]);
        printf ("%c\n", original_list[i]->key[3]); 
    }
    //printf ("here in linked_l_handler \n"); 
    //printf ("t_ID is: %d and num total is: %d \n", t_ID, num_total); 
    int temp_thread_ID = t_ID; 
    //printf ("threadID is: %d \n", t_ID); 
    //printf ("num_total is: %d\n", num_total); 
    printf ("temp_thread_ID is: %d, num_total is: %d, t_id is: %d\n", temp_thread_ID, num_total, t_ID); 
    for (temp_thread_ID; temp_thread_ID < num_total; temp_thread_ID += num_threads) {
            hash_num = naive_hasher(original_list[temp_thread_ID]->key);
            printf ("hashz num is: %d\n", hash_num); 
    printf ("before insertion\n"); 
        //hash_and_insert(temp_thread_ID); 
        printf ("INSERTED \n"); 
    }
}

/* Fowler/Noll/Vo (FNV) hash function, variant 1a: found here on stack exchange:
https://codereview.stackexchange.com/questions/85556/simple-string-hashing-algorithm-implementation */
static size_t fnv1a_hash(const char* cp)
{
    if (cp == NULL){
        printf ("this is null \n");
    }
    printf ("cp is %s\n", *cp);
    printf ("inside hasher \n");
    size_t hash = 0x811c9dc5;
    while (*cp) {
        hash ^= (unsigned char) *cp++;
        hash *= 0x01000193;
    }
    return (hash % number_of_lists);
}

void create_split_list(){
    //create the heads
    split_list = malloc(number_of_lists * sizeof(SortedList_t*));
    int i = 0;
    while (i < number_of_lists){
        split_list[i] = malloc(sizeof(SortedList_t));
        split_list[i]->prev = split_list[i];
        split_list[i]->next = split_list[i];
        split_list[i]->key = NULL;
        i++;
    }
}

void format_flags(){
    strcpy (print_field_flag, "list-");

    if (strlen(yieldopts) ==0){
        strcat (print_field_flag, "none");
    }
    else {
        strcat (print_field_flag, yieldopts);
    }

    if (mutex_flag == true){
        strcat(print_field_flag, "-m");
    }
    else if (spinlock_flag == true){
        strcat(print_field_flag, "-s");
    }
    else {
        strcat(print_field_flag, "-none");
    }
}

/* printing: the name of the test, which is of the form: list-yieldopts-syncopts: where
yieldopts = {none, i,d,l,id,il,dl,idl}
syncopts = {none,s,m}
the number of threads (from --threads=)
the number of iterations (from --iterations=)
the number of lists (always 1 in this project)
the total number of operations performed: threads x iterations x 3 (insert + lookup + delete)
the total run time (in nanoseconds) for all threads
the average time per operation (in nanoseconds).*/ 


void printdata() {
    int num_operations_performed = num_threads * num_iterations * 3;
    long total_run_time; 
    long average_thread_time; 
    format_flags(); 
    total_run_time = compute_total_time(); 
    average_thread_time = compute_average_thread_time(num_operations_performed); 
    long average_time_per_operation = total_run_time/num_operations_performed; 
    printf ("%s,%d,%d,%d,%d,%ld,%ld,%ld\n", print_field_flag, num_threads, num_iterations, number_of_lists, num_operations_performed, total_run_time, average_time_per_operation, average_thread_time); 

}

long compute_average_thread_time (int num_operations_performed){
    long acc = 0; 
    int iterator;  
    for (iterator=0; iterator<= thread_timer_counter; iterator++){
        acc = acc + thread_timer[iterator]; 
    }
    return acc/num_operations_performed; 
}

long compute_total_time() {
    long curr_time_sec_end = (long) end_time.tv_sec;
    long curr_time_ms_end = end_time.tv_nsec/1000000000;
    long curr_time_sec =(long)start_time.tv_sec;
    long curr_time_ms = start_time.tv_nsec/1000000000;
    long total_ns = (curr_time_sec_end +  curr_time_ms_end) - (curr_time_ms + curr_time_ms);
    return total_ns; 
}

void createList(){
   num_total = num_threads * num_iterations;
    /*linked_l = malloc(sizeof(SortedList_t));
    linked_l->next = linked_l;
    linked_l->prev = linked_l;
    linked_l->key = NULL;*/
    //printf ("createList num_total is: %d\n", num_total); 

    int counter =0; 
    original_list = malloc(num_total * sizeof(SortedListElement_t*));

    
    for (counter; counter < num_total; counter++){
        original_list[counter] = malloc(sizeof(SortedListElement_t));
        original_list[counter]->prev = NULL;
        original_list[counter]->next = NULL; 
        int i; 
        char *alphakey = (char *)malloc(sizeof(char)*5); 
        const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (i = 0; i < 5; i++){
            if (i< 4){
            int alpha_num = rand() % (sizeof (alphabet) - 1);
            *(alphakey) = alphabet[alpha_num];
            printf ("char we are inserting is: %c\n", alphabet[alpha_num]);
            alphakey++;

            }
            else if (i == 4){
                *(alphakey)= '\0';
                char *alphakey_temp = (char *)malloc(sizeof(char)*5); 
                alphakey_temp = alphakey-4; 
                original_list[counter]->key = alphakey_temp;
                printf ("finished inserting, original_list [counter]->key is: %s\n", original_list[counter]->key); 
            }            
        }
        printf ("in the end of creation loop original_list [counter]->key is: %s\n", original_list[counter]->key); 
        printf ("in the end of creation loop created object : %p\n", (void*)original_list[counter]);
    }
    //printf("finished\n");
    int i;
    for (i = 0; i < num_total; i++){
        printf ("original_list[counter]->key is: %s\n", original_list[i]->key); 
        printf ("created : %p\n", (void*)original_list[i]);

    }
}

void set_spinlock_lock(int t_ID){
    int spinlock_ret_val; 
    int ll_len; 

    struct timespec thread_start_time; 
    struct timespec thread_end_time;
    long thread_comp_time; 
    clock_gettime(CLOCK_MONOTONIC, &thread_start_time); 

    //printf ("spinlock case \n"); 
    while (__sync_lock_test_and_set(&s_lock, 1));
        printf( "t ID in spinlock is: %d\n", t_ID); 
        do_computation_insert(t_ID); 
    __sync_lock_release(&s_lock);

    while (__sync_lock_test_and_set(&s_lock, 1));
         ll_len = check_list_len(); 
    __sync_lock_release(&s_lock);

    while (__sync_lock_test_and_set(&s_lock, 1));
         do_computation_lookup_to_delete(t_ID); 
    __sync_lock_release(&s_lock);

    clock_gettime(CLOCK_MONOTONIC, &thread_end_time); 
    compute_time_difference(thread_start_time, thread_end_time); 
}

void set_mutex_lock(int t_ID){
    int mutex_ret_val;
    int ll_len; 
    struct timespec thread_start_time; 
    struct timespec thread_end_time;
    long thread_comp_time; 
    clock_gettime(CLOCK_MONOTONIC, &thread_start_time); 
    //printf ("mutexlock case \n"); 
    mutex_ret_val = pthread_mutex_lock(&m_lock);
    if (mutex_ret_val == -1) {
        printf ("could not set mutex lock \n"); 
    }
    do_computation_insert(t_ID); 
    
    pthread_mutex_unlock(&m_lock);  

    ///////////////////////////////////////////
    mutex_ret_val = pthread_mutex_lock(&m_lock);
    if (mutex_ret_val == -1) {
        printf ("could not set mutex lock \n"); 
    }
    ll_len = check_list_len(); 
    
    pthread_mutex_unlock(&m_lock);  

    ///////////////////////////////////////////
    mutex_ret_val = pthread_mutex_lock(&m_lock);
    if (mutex_ret_val == -1) {
        printf ("could not set mutex lock \n"); 
    }
    do_computation_lookup_to_delete(t_ID); 
    pthread_mutex_unlock(&m_lock); 

    clock_gettime(CLOCK_MONOTONIC, &thread_end_time); 
    compute_time_difference(thread_start_time, thread_end_time); 
}

void compute_time_difference (struct timespec start_time, struct timespec end_time){
    long curr_time_sec_end = (long) end_time.tv_sec;
    long curr_time_ms_end = end_time.tv_nsec/1000000000;
    long curr_time_sec_start =(long)start_time.tv_sec;
    long curr_time_ms_start = start_time.tv_nsec/1000000000;
    long total_ns = (curr_time_sec_end +  curr_time_ms_end) - (curr_time_ms_start + curr_time_ms_start);
    thread_timer[thread_timer_counter] = total_ns; 
    //printf ("this operation took: %ld sec\n", total_ns); 
    thread_timer_counter ++; 
}

void do_computation_delete(SortedListElement_t *found_element) {
    if (mutex_flag == true){
        pthread_mutex_lock(&m_lock);
    }
    else if (spinlock_flag == true){
        while (__sync_lock_test_and_set(&s_lock, 1));
    }
            
    /////////////////////////////////////////////
    int del_res; 
    del_res = SortedList_delete (found_element); 
    if (del_res == 1){
        printf ("could not delete the node\n");
    }
    /////////////////////////////////////////////
    if (mutex_flag == true){
                pthread_mutex_unlock(&m_lock);  

    }
    else if (spinlock_flag == true){
        __sync_lock_release(&s_lock);
    }
}
void  do_computation_lookup_to_delete (int t_ID) {
    int i;
    int temp_thread_ID = t_ID; 
    SortedListElement_t *found_element; 
    SortedListElement_t *find_me;  
    while (temp_thread_ID < num_total) {
        find_me = original_list[temp_thread_ID]; 
        for (i = 0; i < number_of_lists; i++){
            found_element = SortedList_lookup (split_list[i], find_me->key); 
            //printf ("found element\n"); 
            if (found_element != NULL){
                do_computation_delete (found_element); 
                break; 
            }
        }
        
        temp_thread_ID++; 
    } 
    //printf ("exiting thread \n");
 return; 
}

void *linked_l_handler(void *vargp) {
    int ll_len; 
    int t_ID = *((int *) vargp);
    printf ("t_id is: %d\n", t_ID);  
    if (mutex_flag == true){
        set_mutex_lock(t_ID);
    }

    else if (spinlock_flag == true){
        set_spinlock_lock(t_ID);
    }

    else {
        do_computation_insert(t_ID); 
        ll_len = check_list_len(); 
        do_computation_lookup_to_delete(t_ID);
    }
    
    pthread_exit(NULL); 
    
}

void set_flags(char* optarg){ 

    if(strcmp("m", optarg)== 0){    
        mutex_flag = true; 
        lockflag_type[0] = 'm'; 
        lockflag_type[1] = '\0'; 
    }

    if(strcmp("s", optarg)== 0){    
        spinlock_flag = true; 
        lockflag_type[0] = 's';  
        lockflag_type[1] = '\0'; 
  
    }
    else {
        lockflag_type[0]= 'n';
        lockflag_type[1] = 'o'; 
        lockflag_type[2] = 'n'; 
        lockflag_type[3] = 'e'; 
        lockflag_type[4] = '\0'; 
    }
} 

int check_list_len() {
    int i = 0; 
    int acc; 
    while (i < number_of_lists){
        acc = acc + SortedList_length(split_list[i]);    
        i++;
    }
    return acc; 
} 


int main (int argc, char **argv) {
    int c; 
    int i; 

    while (1)
    {
        int option_index = 0;
        c = getopt_long(argc, argv, "abc:d:f", long_options, &option_index);
        
        if (c == -1) {
            break;
        }
        switch (c){
            case 'T':
                if (optarg) {
                    num_threads = atoi(optarg);
                }
                break;
            case 'S':
                set_flags(optarg);
                break;
            case 'I':
                if (optarg) {
                    num_iterations = atoi(optarg);
                }
                break;
            case 'L':
                if (optarg) {
                    number_of_lists = atoi(optarg);
                }
                break;
            case 'Y':
                if (optarg) {
                    int num_optarg_chars; 
                    int pos_counter = 0; 
                    num_optarg_chars = strlen(optarg); 
                    while (pos_counter != num_optarg_chars) {
                        yieldopts[pos_counter] = optarg[pos_counter]; 
                        
                        if (optarg[pos_counter] == 'i'){
                            opt_yield = opt_yield | INSERT_YIELD; 
                        }
                        else if (optarg[pos_counter] == 'd'){
                            opt_yield = opt_yield | DELETE_YIELD; 

                        }
                        else if (optarg[pos_counter] == 'l'){
                            opt_yield = opt_yield | LOOKUP_YIELD; 
                        }
                        pos_counter++; 
                    }
                }

                break;
            case '?':
                fprintf (stderr, "bogus args \n");
                fflush(stderr);
                exit (1); 
                break; 
            default:
                exit (1);
        }
    }
  
    createList();
    create_split_list(); 
    clock_gettime(CLOCK_MONOTONIC, &start_time); 
    /*int c1 =0; 
    for (c1; c1 < num_total; c1++){
        printf ("checking creation of : %p\n", (void*)original_list[c1]);
    }*/
    pthread_t *add_thread = malloc((sizeof(pthread_t)*num_threads)); 
    int *arg = malloc(sizeof(*arg));
    //printf ("got here \n"); 
    for (i=0; i < num_threads; i++){
        *arg = i;
        //printf ("before, num_total is: %d\n", num_total); 

        pthread_create(&add_thread[i], NULL, linked_l_handler, (void*) (arg));
    }
    
    for (i =0; i < num_threads; i++){
        pthread_join(add_thread[i], (void**)NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    if (check_list_len() != 0){
        fprintf(stderr, "Length of List After Computation is %d, not 0", check_list_len()); 
        exit (2); 
    }
    printf ("made it to the end\n"); 
    printdata(); 
    exit (0);
    
}