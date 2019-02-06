#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
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

static struct option long_options[] = {
    {"threads", required_argument, 0, 'T' },
    {"iterations", required_argument, 0, 'I' },
    {0, 0, 0, 0}};

int main(int argc, char **argv) {
    int c; 
    long long counter = 0;
    int num_threads = 1;
    int num_iterations = 1;
    while (1){
        int option_index = 0;
        c = getopt_long(argc, argv, "abc:d:f", long_options, &option_index);
        
        switch (c){
            case 'T':
                if (optarg) {
                    num_threads = atoi(optarg);
                }
                break;
            case 'T':
                if (optarg) {
                    num_iterations = atoi(optarg);
                }
                break;
        }
    }
    //initialize time
    timespec curr_time = clock_gettime();
    time_t curr_time_sec = curr_time.tv_sec;
    long curr_time_ms = curr_time.tv_nsec;
}
