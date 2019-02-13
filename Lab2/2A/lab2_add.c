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
#define _GNU_SOURCE

int num_threads = 1;
int num_iterations = 1;
long long counter = 0;
long long *counter_p = &counter;
struct timespec start_time;
struct timespec end_time;
char test_name[50];
bool yield_flag = false; 
bool mutex_flag = false; 
pthread_mutex_t m_lock = PTHREAD_MUTEX_INITIALIZER; 
bool spinlock_flag = false; 
volatile int s_lock = 0;
bool compare_and_swap_flag = false; 

void print_data ();
void set_flags(char* optarg); 
void *pre_handler_processing(void *vargp); 
void set_spinlock_lock(); 
void set_mutex_lock();
void set_compare_and_swap_lock(int num);
void add_computation (); 


static struct option long_options[] = {
    {"threads", required_argument, 0, 'T' },
    {"iterations", required_argument, 0, 'I' },
    {"yield", no_argument, 0, 'Y' },
    {"sync", required_argument, 0, 'S' },
    {0, 0, 0, 0}};

void add(long long *pointer, long long value) {
    long long sum = *pointer + value;
    *pointer = sum;
}

struct add_args
{
    long long *struct_counter_p;
    long long struct_counter;
};

void *pre_handler_processing(void *vargp) {
    if (yield_flag == true) {
        sched_yield(); 
    } 

    //now check for mutex/spinlock/compare&swap
    if (mutex_flag == true) {
        set_mutex_lock(); 
    }

    else if (spinlock_flag == true) {
        set_spinlock_lock(); 
    }

    else if (compare_and_swap_flag == true) {
        int i = 0; 
        for (i; i < num_iterations; i++)
            set_compare_and_swap_lock(1);
        for (i =0; i < num_iterations; i++)
            set_compare_and_swap_lock(-1);
    }

    else {    // normal compare 
        add_computation(); 
    }
}

void add_computation () {
    int i = 0;
    for (i; i < num_iterations; i ++) {
        add (counter_p, 1);
    }
    
    for (i; i < num_iterations; i ++) {
        add (counter_p, -1);
    }
}

void set_mutex_lock(){
    int mutex_ret_val; 
    mutex_ret_val = pthread_mutex_lock(&m_lock);
    if (mutex_ret_val == -1) {
        printf ("could not set mutex lock \n", mutex_ret_val);
        exit (1);  
    }
    add_computation(); 
    pthread_mutex_unlock(&m_lock);  
}

void set_spinlock_lock(){
    int spinlock_ret_val; 
    while (__sync_lock_test_and_set(&s_lock, 1));
        add_computation(); 
    __sync_lock_release(&s_lock);
}

void set_compare_and_swap_lock(int num){
    long long original = *counter_p; 
    long long new;  
    while (__sync_val_compare_and_swap(counter_p, original, new) != original) {
        new = original + num;
    }
}

/*the name of the test (add-none for the most basic usage)
the number of threads (from --threads=)
the number of iterations (from --iterations=)
the total number of operations performed (threads x iterations x 2, the "x 2" factor because you add 1 first and then add -1)
the total run time (in nanoseconds)
the average time per operation (in nanoseconds).
the total at the end of the run (0 if there were no conflicting updates)*/

void print_data(){
    if (strlen(test_name) == 0){
        if (yield_flag == true){
            strcpy(test_name, "add-yield-none");
        }
        else {
            strcpy(test_name, "add-none");
        }
    }
    time_t curr_time_sec_end = end_time.tv_sec;
    long curr_time_ms_end = end_time.tv_nsec;
    time_t curr_time_sec = start_time.tv_sec;
    long curr_time_ms = start_time.tv_nsec;
    int num_operations = 2 * num_threads * num_iterations;
    long total_ns = curr_time_ms_end - curr_time_ms;
    long average_time_per_operation = total_ns/num_operations;
    printf ("%s,%d,%d,%d,%ld,%ld,%d\n", test_name, num_threads, num_iterations, num_operations, total_ns, average_time_per_operation, counter);
}

void set_flags(char* optarg){
    const char add_none [50]= "add-none";
    const char add_m [50]= "add-m"; 
    const char add_s [50]= "add-s"; 
    const char add_c [50]= "add-c"; 
    const char add_yield_none [50]= "add-yield-none"; 
    const char add_yield_m [50]= "add-yield-m"; 
    const char add_yield_s [50]= "add-yield-s"; 
    const char add_yield_c [50]= "add-yield-c"; 


    char m[] = "m"; 
    char c[] = "c"; 
    char s[] = "s"; 
    char *letter_m = &m[0]; 
    char *letter_c = &c[0]; 
    char *letter_s = &s[0]; 


    if (yield_flag == false) { 
        if (strcmp(optarg, letter_m) == 0){
            yield_flag = false; 
            mutex_flag = true; 
            strcpy (test_name, add_m); 
            return;
        }

        if (strcmp(optarg, letter_s) == 0){
            yield_flag = false; 
            spinlock_flag = true;
            strcpy (test_name, add_s); 
            return;
        }

        if (strcmp(optarg, letter_c) == 0){
            yield_flag = false; 
            compare_and_swap_flag = true;
            strcpy (test_name, add_c); 
            return;
        }
        else {
            yield_flag = false; 
            mutex_flag = false; 
            spinlock_flag = false; 
            compare_and_swap_flag = false; 
             strcpy (test_name, add_none); 
             return;   
        }
    }

    else {
        if (strcmp(optarg, letter_m) == 0){
            yield_flag = true; 
            mutex_flag = true;        
            strcpy (test_name, add_yield_m); 
            return; 
        }

        else if (strcmp(optarg, letter_s) == 0){
            yield_flag = true; 
            spinlock_flag = true;        
            strcpy (test_name, add_yield_s); 
            return;       
        }

        else if (strcmp(optarg, letter_c) == 0){
            yield_flag = true; 
            compare_and_swap_flag = true; 
            strcpy (test_name, add_yield_c);  
            return;      
        }
        else {
            yield_flag = true; 
            mutex_flag = false; 
            spinlock_flag = false; 
            compare_and_swap_flag = false;
            strcpy (test_name, add_yield_none); 
        }

    }
    
} 


int main(int argc, char **argv) {
    int c;
    int i =0;
    char *ret = NULL;
    
    clock_gettime(CLOCK_MONOTONIC, &start_time); //monotonic isn't affected by discountinued jobs
    
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
            case 'I':
                if (optarg) {
                    num_iterations = atoi(optarg);
                }
                break;
            case 'S':
                set_flags(optarg); 
                break;
            case 'Y':
                yield_flag = true; 
                break;
            case '?':
                    fprintf (stderr, "bogus args \n");
                    fflush(stderr);
                    exit (1); 
            default:
                break;
        }
    }

    //thread processing
    pthread_t add_thread [num_threads];
    for (i; i < num_threads; i++){
        pthread_create(&add_thread[i], NULL, pre_handler_processing, NULL);
    }
    
    for (i; i < num_threads; i++){
        pthread_join(add_thread[i], (void**)ret);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    print_data ();
    
    if (counter != 0){
        exit (2); 
    }
    exit (0); 
}