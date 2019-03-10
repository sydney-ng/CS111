#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include "mraa/aio.h"
#define T_PORT 1
#define B_PORT 60
mraa_aio_context T;
mraa_gpio_context B;
mraa_result_t status = MRAA_SUCCESS;
FILE * log_file_name = NULL; 
/* https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm*/

void read_values(mraa_aio_context T, mraa_gpio_context B);
void print_report(struct tm * time_struct, float T_val); 
void initialize_sensors (); 

void initialize_sensors (){
    //intialize
    T = mraa_aio_init(T_PORT);
    B = mraa_gpio_init(B_PORT);
    mraa_gpio_dir(B, MRAA_GPIO_IN);

    if (T == NULL || B == NULL) {
        fprintf(stderr, "Failed to initialize AIO or GPIO \n");
    }
    
    //Read from them
    read_values(T, B);
    
    //Close Them
    mraa_aio_close(T);
    mraa_gpio_close(B);
}

void read_values(mraa_aio_context T, mraa_gpio_context B){
    float T_val;
    float B_val;
    time_t rawtime;
    struct tm * time_struct;
    
    printf ("MADE IT HERE!!!!!!\n"); 

    time_struct = localtime(&rawtime);
    T_val = mraa_aio_read(T);
    B_val = mraa_gpio_read(B);
    
    if (T_val == -1 || B_val == -1) {
        fprintf(stderr, "Failed to read from a sensor \n");
    }
    else {
        printf ("val of T: %d, val of B: %d \n", T_val, B_val);
    }

    print_report (time_struct, T_val); 
}

void print_report(struct tm * time_struct, float T_val){
    int hr = time_struct->tm_hour;
    int min = time_struct->tm_min;
    int sec = time_struct->tm_sec; 
    char buf[100];

    fprintf (stdout, "%02d:%02d:%02d %0.1f\n", hr, min, sec, T_val);

    if (log_file_name != NULL){
        fprintf(log_file_name, "%02d:%02d:%02d %0.1f\n", hr, min, sec, T_val);
    }
    printf ("finished \n");
}

static struct option long_options[] = {
    {"SCALE", required_argument, 0, 'S' },
    {"PERIOD", required_argument, 0, 'P' },
    {"STOP", no_argument, 0, 'B' },
    {"START", no_argument, 0, 'E' },
    {"LOG", required_argument, 0, 'L' },
    {"OFF", no_argument, 0, 'O' },
    {0, 0, 0, 0}};

int main(int argc, char **argv) {
    bool exit_one;
    int c;
    
    printf ("here in the beginning\n");
    while (1){
        int option_index = 0;
        c = getopt_long(argc, argv, "abc:d:f", long_options, &option_index);
        switch (c){
            case 'S':
                break;
            case 'P':
                break;
            case 'B':
                break;
            case 'E':
                break;
            case 'L':
                log_file_name = fopen(optarg, "a");
                break;
            case 'O':
                break;
            case '?':
                fprintf (stderr, "Invalid Command Passed");
                fflush(stderr);
                exit_one = true;
                break;
            default:
                break;
        }
         if (c == -1){
            break;
        }
    }
    initialize_sensors(); 
}
