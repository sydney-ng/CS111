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
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>


#define T_PORT 1
mraa_aio_context T;
mraa_result_t status = MRAA_SUCCESS;
FILE * log_file_name = NULL; 
bool farenheit_flag = true; 
bool generate_reports_flag = true; 
bool exit_one;
int period = 1;
int port_num = -1;
char * ID = NULL; 
int sd;

//socket global variables
struct sockaddr_in serv_addr;
struct hostent * server;
char * tcp_server_host = NULL; 
/* https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm*/
/*https://www.tutorialspoint.com/unix_sockets/socket_client_example.htm*/
void turn_off(); 
bool parse_command2 (char * curr_command);
void process_command_options (char * command_input);
void read_values();
void print_report(struct tm * time_struct, float T_val); 
void initialize (); 
float format_values (float temp_T_val); 
void parse_command(char * command_input); 
struct tm * get_time(); 
void log_ID(); 

void log_ID(){
	char buf[100];
    sprintf(buf, "ID=%s\n", ID);
	dprintf(sd, "ID=%s\n", ID);
	if (generate_reports_flag == true){
		        fflush(log_file_name);
	fprintf(log_file_name, "ID=%s\n", ID);
        fflush(log_file_name);
    }
}

void initialize (){
    //intialize sensors 
    T = mraa_aio_init(T_PORT);

    if (T == NULL) {
        fprintf(stderr, "Failed to initialize AIO \n");
    }
    //initialize socket 
    int connect_descriptor;
    sd = socket (AF_INET, SOCK_STREAM, 0);
    if (sd == -1){
    	fprintf(stderr, "%s\n", "couldn't initialize socket");
    	exit(1);
    }

    server = gethostbyname(tcp_server_host);
    if (server == NULL) {
      fprintf(stderr,"%s\n", "couldn't get host by name");
      exit(1);
   }

   //printf ("initialized host name \n");
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(port_num);

   //printf ("about to connect \n");
   connect_descriptor = connect (sd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)); 
   //printf ("connect descriptor is %d\n", connect_descriptor);
   if (connect_descriptor == -1) {
   		fprintf(stderr, "%s\n", "couldn't connect to server");
   		exit (1); 
    }
    //printf ("finisehd initializing \n");
}

void process_command_options (char * command_input) {
    char buf[100];
    
    if(strcmp(command_input, "SCALE=F") == 0) {
        farenheit_flag = true;
		//sprintf(buf, "%s\n", "SCALE=F");
        //dprintf(sd, "%s\n", "SCALE=F");
        if (generate_reports_flag){
        	        fflush(log_file_name);
fprintf(log_file_name, "%s\n", "SCALE=F");
        	fflush(log_file_name);
        }
    }
    else if(strcmp(command_input, "OFF") == 0) {
        turn_off();
    }
   else if(strcmp("command_input", "SCALE=C") == 0) {
        farenheit_flag = false; 
		//sprintf(buf, "%s\n", "SCALE=C");
        //dprintf(sd, "%s\n", "SCALE=C");
        if (generate_reports_flag){
        	        fflush(log_file_name);
fprintf(log_file_name, "%s\n", "SCALE=C");
        	fflush(log_file_name);
    	}
   }
   else if(strcmp(command_input, "STOP") == 0) {
        //sprintf(buf, "%s\n", "STOP");
        //dprintf(sd, "%s\n", "STOP");
        if (generate_reports_flag){
                    fflush(log_file_name);
fprintf(log_file_name, "%s\n", "STOP");
        	fflush(log_file_name);
        }
        generate_reports_flag = false; 
    }
    else if(strcmp(command_input, "START") == 0) {
        generate_reports_flag = true; 
        //sprintf(buf, "%s\n", "START");
        //dprintf(sd, "%s\n", "START");
                fflush(log_file_name);
fprintf(log_file_name, "%s\n", "START");
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
            //sprintf(buf, "%s\n", ret);
       		//dprintf(sd, "%s\n", ret);
            //printf ("this is period \n"); 
            if (generate_reports_flag){
                //printf("writing to log file for period \n"); 
				        fflush(log_file_name);
fprintf(log_file_name, "%s\n", ret);
        		fflush(log_file_name);            
        	}
        }

        else if (ret = strstr (command_input, "LOG")) {
            //sprintf(buf, "%s\n", ret);
       		//dprintf(sd, "%s\n", ret);
            //printf ("this is period \n"); 
                //printf("writing to log file for period \n"); 
				fflush(log_file_name);
				fprintf(log_file_name, "%s\n", ret);
        		fflush(log_file_name);            
        
        }
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
    //printf ("in read values\n");
    T_val = format_values (temp_T_val); 
     
    print_report (time_struct, T_val);
}

float format_values (float temperature) {
    const int termistor_val = 4275;            
	float R0 = 100000.0;
	float R = 1023.0/(temperature) - 1.0;
	R = R * R0;
	float t2 = 1.0/(log(R/R0)/termistor_val + 1/298.15) - 273.15; 
	if (farenheit_flag == true) { //convert temperature to F
		t2 = (t2 * 1.8) + 32; 
	}
	//printf ("temp reading is: %f\n", t2);
	//fflush(stdout); 
	return t2;  
}

void print_report(struct tm * time_struct, float T_val){
    int hr = time_struct->tm_hour;
    int min = time_struct->tm_min;
    int sec = time_struct->tm_sec; 

    char buf[100];
	sprintf(buf, "%02d:%02d:%02d %0.1f\n", hr, min, sec, T_val);
    dprintf(sd, "%02d:%02d:%02d %0.1f\n", hr, min, sec, T_val);
            fflush(log_file_name);
fprintf(log_file_name, "%02d:%02d:%02d %0.1f\n", hr, min, sec, T_val);
    fflush(log_file_name);

    sleep (period); 
}

void turn_off (){
    struct tm * time_struct;

    time_struct = get_time(); 
    int hr = time_struct->tm_hour;
    int min = time_struct->tm_min;
    int sec = time_struct->tm_sec; 
    char buf [500];
    sprintf(buf, "OFF\n%02d:%02d:%02d SHUTDOWN\n", hr, min, sec);
    dprintf(sd, "OFF\n%02d:%02d:%02d SHUTDOWN\n", hr, min, sec);
    fflush(log_file_name);
	fprintf(log_file_name, "OFF\n%02d:%02d:%02d SHUTDOWN\n", hr, min, sec);
    fflush(log_file_name);

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
	//printf ("YOOOO IM IN MAIN BEGINNING \n");
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
            case 'I':
                ID = optarg; 
                break;
            case 'H':
            	//tcp_server_host = (char*) malloc((strlen(optarg +1))*sizeof(char));
            	tcp_server_host = optarg; 
            	if (tcp_server_host == NULL){
            		fprintf (stderr, "initial parse couldn't retrieve host name\n");
            	}
                break;
            case 'L':
           		//printf ("optarg for log is %s \n", optarg); 
                log_file_name = fopen(optarg, "a");
        		if (log_file_name == NULL){
        		}
                //printf ("LOGFILE NAME IS : %s\n", log_file_name); 
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

    if (port_num == -1 || log_file_name == NULL || tcp_server_host == NULL || ID == NULL) {
    	fprintf (stderr, "not all options were passed in\n"); 
    }

    initialize(); 
    //printf ("after initialize\n");

    log_ID(); 

    struct pollfd fds[1];
    fds[0].fd = sd;
    fds[0].events = POLLIN; 

    while (1) {
    	//printf ("in while loop\n");
        FILE* data_received;
        int ret;
        char command_input[100];
        //printf ("in while loop\n");
        read_values(); 
        //printf ("polling!\n"); 
        ret = poll(fds, 1, 0);

        if (ret == -1) {
            fprintf (stderr, "polling error \n");
            exit(1);
        }
        
        else if (fds[0].revents == POLLIN) {
            //printf ("send to parse command \n");
            data_received = fdopen(sd, "r");
            fgets(command_input, 100, data_received);
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
