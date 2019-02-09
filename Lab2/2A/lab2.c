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
#define _GNU_SOURCE

int num_threads = 1;
int num_iterations = 1;
long long counter_val = 1;
long long *counter_p = &counter_val;
struct timespec start_time;
struct timespec end_time;


static struct option long_options[] = {
    {"threads", required_argument, 0, 'T' },
    {"iterations", required_argument, 0, 'I' },
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

void *add_handler (void *vargp) {
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

int main(int argc, char **argv) {
    int c;
    int i =0;
    char *ret = NULL;
    
    clock_gettime(CLOCK_MONOTONIC, &start_time); //monotonic isn't affected by discountinued jobs
    time_t curr_time_sec = start_time.tv_sec;
    long curr_time_ms = start_time.tv_nsec;
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
            case '?':
                printf ("invalid command \n");
            default:
                break;
        }
    }
    //thread processing
    pthread_t add_thread [num_threads];
    for (i; i < num_threads; i++){
        pthread_create(&add_thread[num_threads], NULL, add_handler, NULL);
        pthread_join(add_thread[num_threads], (void**)ret);
    }
    
    printf ("value of counter is now: %ld \n", counter_val);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    
    time_t curr_time_sec_end = end_time.tv_sec;
    long curr_time_ms_end = end_time.tv_nsec;
    
    print_data ();
}

// /usr/local/cs/bin/gnuplot
