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

int opt_yield = 0; 
int num_threads = 1;
int num_iterations = 1;
SortedListElement_t **original_list;
SortedList_t *linked_l;
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
static struct option long_options[] = {
    {"threads", required_argument, 0, 'T' },
    {"iterations", required_argument, 0, 'I' },
    {"yield", required_argument, 0, 'Y' },
    {"sync", required_argument, 0, 'S' },
    {0, 0, 0, 0}
};

SortedList_t *m_list; 
SortedListElement_t **m_empty_list;

void *linked_l_handler(void *vargp);
void createList(); 
void printdata();
void format_flags();
void do_computation_insert(int t_ID);  
void  do_computation_lookup_to_delete(int t_ID);
void do_computation_delete(SortedListElement_t *found_element);  
void  do_computation_len();


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
	format_flags(); 

    long curr_time_sec_end = (long) end_time.tv_sec;
    long curr_time_ms_end = end_time.tv_nsec/1000000000;
    long curr_time_sec =(long)start_time.tv_sec;
    long curr_time_ms = start_time.tv_nsec/1000000000;

    long total_ns = (curr_time_sec_end +  curr_time_ms_end) - (curr_time_ms + curr_time_ms);

	int num_operations_performed = num_threads * num_iterations * 3;
	long average_time_per_operation = total_ns/num_operations_performed; 
	
    printf ("%s,%d,%d,1,%d,%ld,%ld\n", print_field_flag, num_threads, num_iterations, num_operations_performed, total_ns, average_time_per_operation); 

}
void createList(){
    num_total = num_threads * num_iterations;
	linked_l = malloc(sizeof(SortedList_t));
	linked_l->next = linked_l;
	linked_l->prev = linked_l;
	linked_l->key = NULL;
	int i; 

	
	//printf ("createList num_total is: %d\n", num_total); 

	int counter =0; 
	original_list = malloc(num_total * sizeof(SortedListElement_t*));
	
	for (counter; counter < num_total; counter++){
		original_list[counter] = malloc(sizeof(SortedListElement_t));
		original_list[counter]->prev = NULL;
		original_list[counter]->next = NULL; 
		char alphakey[5];
		const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		for (i = 0; i < 4; i++){
				int alpha_num = rand() % (sizeof (alphabet) - 1);
				alphakey[i] = alphabet[alpha_num];
			}
		alphakey[4] = '\0';
		original_list[counter]->key = alphakey; 
		//printf ("created : %p\n", (void*)original_list[counter]);

	}
	//printf("finished\n");
}

void set_spinlock_lock(int t_ID){
    int spinlock_ret_val; 
    //printf ("spinlock case \n"); 
    while (__sync_lock_test_and_set(&s_lock, 1));
        do_computation_insert(t_ID); 
    __sync_lock_release(&s_lock);

    while (__sync_lock_test_and_set(&s_lock, 1));
         do_computation_len(t_ID); 
    __sync_lock_release(&s_lock);

    while (__sync_lock_test_and_set(&s_lock, 1));
         do_computation_lookup_to_delete(t_ID); 
    __sync_lock_release(&s_lock);

}

void set_mutex_lock(int t_ID){
    int mutex_ret_val; 
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
    do_computation_len(t_ID); 
    
    pthread_mutex_unlock(&m_lock);  

    ///////////////////////////////////////////
    mutex_ret_val = pthread_mutex_lock(&m_lock);
    if (mutex_ret_val == -1) {
        printf ("could not set mutex lock \n"); 
    }
     do_computation_lookup_to_delete(t_ID); 
    pthread_mutex_unlock(&m_lock);  
}

void do_computation_insert(int t_ID) {
    //printf ("here in linked_l_handler \n"); 
    //printf ("t_ID is: %d and num total is: %d \n", t_ID, num_total); 
    int temp_thread_ID = t_ID; 
    //printf ("threadID is: %d \n", t_ID); 
    //printf ("num_total is: %d\n", num_total); 

    for (temp_thread_ID; temp_thread_ID < num_total; temp_thread_ID += num_threads) {
        //printf ("inside iterating loop\n"); 
        //printf ("temp_thread_ID is: %d \n", temp_thread_ID); 
        //printf ("the one we are inserting is: %p\n", (void*)original_list[temp_thread_ID]);
        SortedList_insert(linked_l, original_list[temp_thread_ID]);
        //printf ("done inserting!\n");
    }
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

int do_computation_len (int t_ID) {
     int linked_l_len; 
    //printf ("after inserting \n");
    //gets the list length
    linked_l_len = SortedList_length(linked_l);
    //printf ("list len is: %d\n", linked_l_len);
    return linked_l_len;  
}
void  do_computation_lookup_to_delete (int t_ID) {

    int temp_thread_ID = t_ID; 
    SortedListElement_t *found_element; 
    SortedListElement_t *find_me;  
    while (temp_thread_ID < num_total) {
        find_me = original_list[temp_thread_ID]; 
        found_element = SortedList_lookup (linked_l, find_me->key); 
        //printf ("found element\n"); 
        if (found_element != NULL){
            do_computation_delete (found_element); 
        }
        temp_thread_ID++; 
    } 
    //printf ("exiting thread \n");
 return; 
}

void *linked_l_handler(void *vargp) {
    int t_ID = *((int *) vargp); 
    if (mutex_flag == true){
        set_mutex_lock(t_ID);
    }

    else if (spinlock_flag == true){
        set_spinlock_lock(t_ID);
    }

    else {
        do_computation_insert(t_ID); 
        do_computation_len(); 
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
    clock_gettime(CLOCK_MONOTONIC, &start_time); 
    int c1 =0; 
	/*for (c1; c1 < num_total; c1++){
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

    if (SortedList_length(linked_l) != 0) {
    	fprintf(stderr, "Length of List After Computation is not 0"); 
        exit (2); 
    }

    printdata(); 
    exit (0);
    
}