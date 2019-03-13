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
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/socket.h>

#define T_PORT 1
mraa_aio_context T;
mraa_result_t status = MRAA_SUCCESS;
FILE * log_file_name = NULL; 
bool farenheit_flag = true; 
bool generate_reports_flag = true; 
bool exit_one;
int period = 1;
int port_num;

//socket global variables
struct sockaddr_in serv_addr;
struct hostent *server;
char tcp_server_host [17] = "lever.cs.ucla.edu"; 
/* https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm*/
/*https://www.tutorialspoint.com/unix_sockets/socket_client_example.htm*/
void turn_off(); 
bool parse_command2 (char * curr_command);
void process_command_options (char * command_input);
void read_values();
void print_report(struct tm * time_struct, float T_val); 
void initialize (); 
float format_values (float temp_T_val, float B_val); 
void parse_command(char * command_input); 
struct tm * get_time(); 

void initialize (){
    //intialize sensors 
    T = mraa_aio_init(T_PORT);

    if (T == NULL) {
        fprintf(stderr, "Failed to initialize AIO \n");
    }

    //initialize socket 
    int sd;
    int connect_descriptor;
    sd = socket (AF_INET, SOCK_STREAM, 0);
    if (sd == -1){
    	fprintf(stderr, "%s\n", "couldn't initialize socket");
    }

    server = gethostbyname(tcp_server_host);
    if (server == NULL) {
      fprintf(stderr,"%s\n", "couldn't get host by name");
   }

    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_num); 


    connect_descriptor = connect (sd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)); 
    if (connect_descriptor == -1) {
    	fprintf(stderr, "%s\n", "couldn't connect to server");
    }
}

void process_command_options (char * command_input) {
    //printf ("in process command options with %s \n", command_input); 
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
        //printf (" this could be period \n"); 
        if (ret = strstr (command_input, "PERIOD=")) {
            ret2 = strstr (command_input, "=");
            period = atoi(ret2+1); 
            //printf ("this is period \n"); 
            if (generate_reports_flag && log_file_name != NULL){
                //printf("writing to log file for period \n"); 
                fprintf(log_file_name, "%s\n", ret);
                        fflush(log_file_name);

            } 
            else {
                printf("%s\n", ret);
            }
        }

        else if (ret = strstr (command_input, "LOG")) {
            printf("%s\n", ret);
            printf ("logfile is: %s\n", log_file_name);
            if (log_file_name != NULL){
                //printf("writing to log file for period \n"); 
                fprintf(log_file_name, "%s\n", ret);
                        fflush(log_file_name);

            }
        }

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
    struct tm * time_struct;

    time_struct = get_time (); 
    temp_T_val = mraa_aio_read(T);
    
    T_val = format_values (temp_T_val); 
     
    print_report (time_struct, T_val);
}

float format_values (float temp_T_val) {
    const int termistor_val = 4275;            
    float R0 = 100000.0; 
    float R = 1023.0/(temp_T_val-1.0);
    R = R * R0; 
    float temp2_T_val; 
    temp2_T_val = 1.0/(log(R/R0)/termistor_val+1/298.15)-273.15; // convert to temperature via datasheet

    if (temp_T_val == -1) {
        fprintf(stderr, "Failed to read from temperature sensor \n");
    }
    else {
        printf ("val of T: %f \n", temp2_T_val);
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
    mraa_aio_close(T);

    exit (0); 
}

static struct option long_options[] = {
    {"scale", required_argument, 0, 'S' },
    {"period", required_argument, 0, 'P' },
    {"stop", no_argument, 0, 'B' },
    {"start", no_argument, 0, 'E' },
    {"log", required_argument, 0, 'L' },
    {"off", no_argument, 0, 'O' },
    {"id", required_argument, 0, 'I' },
    {"host", required_argument, 0, 'H' },
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
            	generate_reports_flag = false; 
                break;
            case 'E':
                generate_reports_flag = true;             	
                break;
            case 'L':
                log_file_name = fopen(optarg, "a");
                break;
            case 'O':
            	turn_off(); 
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
    port_num = atoi(argv[argc - 1]);

    initialize(); 

    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN | POLLHUP | POLLERR; 

    while (1) {
        int ret;
        char command_input[100];
        //printf ("in while loop\n");
        read_values(); 
        //printf ("polling!\n"); 
        fflush(stdout); 
        ret = poll(fds, 1, 0);

        if (ret == -1) {
            printf ("polling error \n");
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

bool parse_command2 (char * curr_command){
    if (curr_command[0] == 'L' && curr_command[1] == 'O' && curr_command[2] == 'G') {
        return true; 
        }
    else {
        return false; 
    }
}

void parse_command(char * command_input) {
    //printf("inside parse command\n" );
    char * curr_command = (char *)malloc(50 * sizeof(char));
    int curr_command_counter = 0; 
    while(command_input != NULL && *command_input != '\n' && curr_command_counter < 50) {
        if (*command_input != ' ' && *command_input != '\n'){
            //printf ("counter is at %d, looking at char %c \n", curr_command_counter, *command_input);
            curr_command[curr_command_counter] = *command_input;
            curr_command_counter ++; 
        }
        else { 
           if (parse_command2(curr_command) == false){
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
           else {
                curr_command[curr_command_counter] = ' ';
                curr_command_counter ++; 
           }
        }
        command_input++;
    }

    curr_command[curr_command_counter] = '\0';
    process_command_options (curr_command); 
}
