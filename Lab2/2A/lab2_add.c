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
char test_name[100] = "add-none";
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
void set_compare_and_swap_lock();
void add_computation (); 


static struct option long_options[] = {
    {"threads", required_argument, 0, 'T' },
    {"iterations", required_argument, 0, 'I' },
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
    if ((yield_flag) == true ) {
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
        set_compare_and_swap_lock();
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
    
    printf ("did the adding \n");
    for (i; i < num_iterations; i ++) {
        add (counter_p, -1);
    }
    printf ("did the subtracting \n");
}

void set_mutex_lock(){
    int mutex_ret_val; 
    mutex_ret_val = pthread_mutex_lock(&m_lock);
    if (mutex_ret_val == -1) {
        printf ("could not set mutex lock \n", mutex_ret_val); 
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

void set_compare_and_swap_lock(){
    /*long long original; 
    long long *original_p = &original;
    long long new; 
    while (__sync_val_compare_and_swap(counter_p, original, new) != true) {
        original = *counter_p; 
        int i = 0;
        for (i; i < num_iterations; i ++) {
            add (original_p, 1);
        }
        
        printf ("did the adding \n");
        for (i; i < num_iterations; i ++) {
            add (original_p, -1);
        }
        printf ("did the subtracting \n");
     }
     new = &original_p; */
} 

void print_data(){
    time_t curr_time_sec_end = end_time.tv_sec;
    long curr_time_ms_end = end_time.tv_nsec;
    time_t curr_time_sec = start_time.tv_sec;
    long curr_time_ms = start_time.tv_nsec;
    int num_operations = 2 * num_threads * num_iterations;
    long total_ns = curr_time_ms_end - curr_time_ms;
    long average_time_per_operation = total_ns/num_operations;
    printf ("%s, %d, %d, %d , %ld, %ld, %d \n", test_name, num_threads, num_iterations, num_operations, total_ns, average_time_per_operation, counter);
}

void set_flags(char* optarg){
    char add_none [50]= "add-none";
    char add_m [50]= "add-m"; 
    char add_s [50]= "add-s"; 
    char add_c [50]= "add-c"; 
    char add_yield_none [50]= "add-yield-none"; 
    char add_yield_m [50]= "add-yield-m"; 
    char add_yield_s [50]= "add-yield-s"; 
    char add_yield_c [50]= "add-yield-c"; 

    if (strcmp(optarg, add_none) == 0){
        yield_flag = false; 
        mutex_flag = false; 
        spinlock_flag = false; 
        compare_and_swap_flag = false; 
    }

    if (strcmp(optarg, add_m) == 0){
        yield_flag = false; 
        mutex_flag = true; 
    }

    if (strcmp(optarg, add_s) == 0){
        yield_flag = false; 
        spinlock_flag = true;    
    }

    if (strcmp(optarg, add_c) == 0){
        yield_flag = false; 
        compare_and_swap_flag = true;      
    }

    if (strcmp(optarg, add_yield_none) == 0){
        yield_flag = true; 
        mutex_flag = false; 
        spinlock_flag = false; 
        compare_and_swap_flag = false; 
    }
    if (strcmp(optarg, add_yield_m) == 0){
        yield_flag = true; 
        mutex_flag = true;       
    }

    if (strcmp(optarg, add_yield_s) == 0){
        yield_flag = true; 
        spinlock_flag = true;       
    }

    if (strcmp(optarg, add_yield_c) == 0){
        yield_flag = true; 
        compare_and_swap_flag = true;       
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
                if (optarg) {
                    printf ("optarg is: %s \n", optarg); 
                }
                set_flags(optarg); 
                break;
            case '?':
                    fprintf (stdout, "bogus args \n");
                    fflush(stdout);
                    exit (1); 
            default:
                break;
        }
    }

    if (mutex_flag == true) {
        pthread_mutex_init(&m_lock, NULL); 
    }
    //thread processing
    pthread_t add_thread [num_threads];
    for (i; i < num_threads; i++){
        pthread_create(&add_thread[num_threads], NULL, pre_handler_processing, NULL);
    }
    
    for (i; i < num_threads; i++){
        pthread_join(add_thread[num_threads], (void**)ret);
    }
    
    if (mutex_flag == true){
        pthread_mutex_destroy(&m_lock); 
    }
    printf ("value of counter is now: %ld \n", counter);
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    print_data ();
}

// /usr/local/cs/bin/gnuplot
