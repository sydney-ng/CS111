#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "mraa/aio.h"
#include <sys/poll.h>
#include <string.h>

#define T_PORT 1
#define B_PORT 60
mraa_aio_context T;
mraa_gpio_context B;
mraa_result_t status = MRAA_SUCCESS;
FILE * log_file_name = NULL; 
bool farenheit_flag = true; 
bool generate_reports_flag = true; 
bool exit_one;
int period = 1;
/* https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm*/

void turn_off(); 
void process_command_options (char * command_input);
void read_values();
void print_report(struct tm * time_struct, float T_val); 
void initialize_sensors (); 
float format_values (float temp_T_val, float B_val); 
void parse_command(char * command_input); 
struct tm * get_time(); 

void initialize_sensors (){
    //intialize
    T = mraa_aio_init(T_PORT);
    B = mraa_gpio_init(B_PORT);
    mraa_gpio_dir(B, MRAA_GPIO_IN);

    if (T == NULL || B == NULL) {
        fprintf(stderr, "Failed to initialize AIO or GPIO \n");
    }

    //Close Them
    //mraa_aio_close(T);
    //mraa_gpio_close(B);
}

void process_command_options (char * command_input) {
    printf ("in process command options with %s \n", command_input); 
    if(strcmp(command_input, "SCALE=F") == 0) {
        farenheit_flag = true;
        if (generate_reports_flag && log_file_name != NULL){
            fprintf(log_file_name, "SCALE=F\n");
                    fflush(log_file_name);

        } 
        else {
            printf ("SCALE=F\n");
        }
    }
    else if(strcmp(command_input, "OFF") == 0) {
        turn_off();
    }
   else if(strcmp("command_input", "SCALE=C") == 0) {
        farenheit_flag = false; 

        if (generate_reports_flag && log_file_name != NULL){
            fprintf(log_file_name, "SCALE=C\n");
                    fflush(log_file_name);

        } 
        else {
            printf ("SCALE=C\n");
        }

   }
   else if(strcmp(command_input, "STOP") == 0) {
        if (generate_reports_flag && log_file_name != NULL){
            fprintf(log_file_name, "STOP\n");
                    fflush(log_file_name);

        } 
            fprintf (stdout, "%s", "STOP\n");
            fflush(stdout);
            generate_reports_flag = false; 
    }
    else if(strcmp(command_input, "START") == 0) {
        generate_reports_flag = true; 
        //printf ("START\n");
        fprintf(log_file_name, "START\n");
                fflush(log_file_name);

    }
    else {
        //printf ("this is not a valid option yet\n");
        char * ret = NULL;
        char * ret2 = NULL;
                char * ret3 = NULL;

        if (ret = strstr (command_input, "PERIOD=")) {
            ret2 = strstr (command_input, "=");
            period = atoi(ret2+1); 

            if (generate_reports_flag && log_file_name != NULL){
                //printf("writing to log file for period \n"); 
                fprintf(log_file_name, "%s\n", ret);
                        fflush(log_file_name);

            } 
            else {
                printf("%s\n", ret);
            }
        }

        if (ret = strstr (command_input, "LOG")) {
            printf("%s\n", ret);
            if (generate_reports_flag && log_file_name != NULL){
                //printf("writing to log file for period \n"); 
                fprintf(log_file_name, "%s\n", ret);
                        fflush(log_file_name);

            }
        }

        /*else if (ret = strstr (command_input, "period=")) {
            ret2 = strstr (command_input, "=");
            period = atoi(ret2+1); 

            if (generate_reports_flag){
                                //printf("writing to log file for period \n"); 
                fprintf(log_file_name, "%s\n", ret);
                        fflush(log_file_name);

            } 
            else {
                printf("%s\n", ret);
            }

        }*/
        
        else {
            fprintf (stderr, "%s", "this is an invalid command./ \n");
            fflush(stderr);
            exit (1); 
        }
    }
    if (generate_reports_flag) {

    }
}

struct tm * get_time() {
    time_t rawtime;
    struct tm * time_struct;

    time_struct = localtime(&rawtime);

    return time_struct; 
}

void read_values(){
    float temp_T_val;
    float T_val; 
    float B_val;
    struct tm * time_struct;

    time_struct = get_time (); 
    temp_T_val = mraa_aio_read(T);
    B_val = mraa_gpio_read(B);
    
    T_val = format_values (temp_T_val, B_val); 
     
    print_report (time_struct, T_val);
}

float format_values (float temp_T_val, float B_val) {
    const int termistor_val = 4275;            
    float R0 = 100000.0; 
    float R = 1023.0/(temp_T_val-1.0);
    R = R * R0; 
    float temp2_T_val; 
    temp2_T_val = 1.0/(log(R/R0)/termistor_val+1/298.15)-273.15; // convert to temperature via datasheet

    if (temp_T_val == -1 || B_val == -1) {
        fprintf(stderr, "Failed to read from a sensor \n");
    }
    else {
        printf ("val of T: %f, val of B: %f \n", temp2_T_val, B_val);
    }

    if (farenheit_flag == true){
        temp2_T_val = (1.8 * temp_T_val) + 32;
    }
   return temp2_T_val; 
}

void print_report(struct tm * time_struct, float T_val){
    int hr = time_struct->tm_hour;
    int min = time_struct->tm_min;
    int sec = time_struct->tm_sec; 
    char buf[100];

    if (generate_reports_flag && log_file_name != NULL){
            fprintf(log_file_name, "%02d:%02d:%02d %0.1f\n", hr, min, sec, T_val);
            fflush(log_file_name);
            //printf("writing to log file for temperature \n"); 
        }
    else {
        fprintf (stdout, "%02d:%02d:%02d %0.1f\n", hr, min, sec, T_val);

    }
    sleep (period); 
}

void turn_off (){
    struct tm * time_struct;

    fprintf (stdout, "%s \n", "OFF"); 
    fprintf(log_file_name, "OFF\n");
    fflush(log_file_name);



    time_struct = get_time(); 
    int hr = time_struct->tm_hour;
    int min = time_struct->tm_min;
    int sec = time_struct->tm_sec; 


    fprintf (stdout, "%s \n", "SHUTDOWN"); 
    fprintf(log_file_name, "%02d:%02d:%02d ", hr, min, sec);
    fprintf(log_file_name, "SHUTDOWN\n");
    fflush(log_file_name);


    mraa_gpio_close(B);
}

static struct option long_options[] = {
    {"scale", required_argument, 0, 'S' },
    {"period", required_argument, 0, 'P' },
    {"stop", no_argument, 0, 'B' },
    {"start", no_argument, 0, 'E' },
    {"log", required_argument, 0, 'L' },
    {"off", no_argument, 0, 'O' },
    {0, 0, 0, 0}};

int main(int argc, char **argv) {

     while (1){
        int c;
        int option_index = 0;
        c = getopt_long(argc, argv, "abc:d:f", long_options, &option_index);
        switch (c){
            case 'S':
                if (*optarg == 'C'){
                    farenheit_flag = false;
                }
                else if (*optarg != 'F'){
                    fprintf (stderr, "Invalid Scale Argument");
                }
                break;
            case 'P':
                period = atoi (optarg); 
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
                exit (1);
                break;
            default:
                break;
        }
         if (c == -1){
            break;
        }
    }
    initialize_sensors(); 

    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    while (1) {
        int ret;
        char command_input[100];
        read_values(); 

        ret = poll(fds, 1, 0);

        if (ret == -1) {
            printf ("polling error \n");
            perror ("poll");
            return 1;
        }
        else if (mraa_gpio_read(B) == 1){
            turn_off();
        //this is a valid command passed
        }
        else if (fds[0].revents == POLLIN) {
            //printf ("send to parse command \n");
            fgets(command_input, 100, stdin);
            parse_command(command_input); 
        }
    }
}

void parse_command(char * command_input) {
    printf("inside parse command\n" );
    char * curr_command = (char *)malloc(50 * sizeof(char));
    int curr_command_counter = 0; 
    while(command_input != NULL && *command_input != '\n' && curr_command_counter < 50) {
        if (*command_input != ' ' && *command_input != '\n'){
            //printf ("counter is at %d, looking at char %c \n", curr_command_counter, *command_input);
            curr_command[curr_command_counter] = *command_input;
            curr_command_counter ++; 
        }
        else { 
            if (curr_command[0] == 'L' && curr_command[1] == 'O' && curr_command[2] == 'G') {
                curr_command[curr_command_counter] = ' ';
                curr_command_counter ++; 
                continue; 
            }
            else {
                curr_command[curr_command_counter] = '\0';
                //printf ("found a space!!\n");
                process_command_options (curr_command); 
                // reset variables 
                curr_command_counter = 0; 
                int i;
                for (i = 0; i < 50; i ++){
                    curr_command [i] = '\0';
                }
            }
            
        }
        command_input++;
    }

    curr_command[curr_command_counter] = '\0';
    process_command_options (curr_command); 
}