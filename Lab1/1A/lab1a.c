#define _POSIX_SOURCE
#include <fcntl.h>
#include <unistd.h>
#undef _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

int fd_table[100];
int starting_fd_number = 0;
static struct option long_options[] = {
    {"rdonly", required_argument, 0, 'R' },
    {"wronly", required_argument, 0, 'B' },
    {"verbose", no_argument, 0, 'V' },
    {"command", no_argument, 0, 'C' },
    {0, 0, 0, 0}};
int command_intput_fd = 0; 
int command_output_fd = 1; 
int command_error_fd = 2;

void parse_command_option (int optind, char **argv, int argc, int fd_table_counter, int starting_fd_number);
void command_to_children (int command_intput_fd, int command_output_fd, int command_error_fd, char *cmd_args);

void parse_command_option (int optind, char **argv, int argc, int fd_table_counter, int starting_fd_number) {
    int index_counter = optind; 
    int arr_counter = 0; 
    int command_flag = 0; 
    char *cmd_args[argc]; 
    char *cmd_name [100];
    int temp_fd_table_counter = fd_table_counter - 3;

    while (index_counter < argc) {
        if (argv[index_counter][0] == '-') {
            if (argv[index_counter] [1] == '-') {
            break; 
            }  
        } 
        else if (command_flag < 4) {
            // input
            if (command_flag == 0){
                starting_fd_number = fd_table_counter - 3;
                command_intput_fd = fd_table[atoi(argv[index_counter])];
                if (atoi(argv[index_counter]) >= fd_table_counter) {
                    fprintf (stderr, "File Descriptor for reading contents is wrong"); 
                    exit (1); 
                }
                temp_fd_table_counter++;
                command_flag ++; 
                }
            // output
            else if (command_flag == 1){
                command_output_fd = fd_table[atoi(argv[index_counter])]; 
                if (atoi(argv[index_counter]) >= fd_table_counter) {
                    fprintf (stderr, "File Descriptor for writing contents is wrong"); 
                     exit (1); 

                }
                command_flag ++; 
                temp_fd_table_counter++;
                }
            // error 
            else if (command_flag == 2){
                command_error_fd = fd_table[atoi(argv[index_counter])];  
                 if (atoi(argv[index_counter]) >= fd_table_counter) {
                    fprintf (stderr, "File Descriptor for reading contents is wrong");
                    exit (1); 
                }
                command_flag ++; 
                temp_fd_table_counter++;
                } 
            // actual command 
            else if (command_flag == 3) {
                cmd_name [0] = argv[index_counter]; 
                cmd_name [1] = NULL; 

                command_flag ++; 
                cmd_args[arr_counter] = argv[index_counter]; 
                arr_counter ++;
            }
        }
        else {
            cmd_args[arr_counter] = argv[index_counter]; 
            //printf ("adding to cmd_arg is: %s \n", argv[index_counter] ); 
            arr_counter++; 
            optind = index_counter;
        }
            //printf ("counter is now : %d and argc is : %d \n", index_counter, argc); 
            index_counter++; 
    }
    cmd_args[arr_counter] = NULL;
    command_to_children (command_intput_fd, command_output_fd, command_error_fd, cmd_args);
}

void command_to_children (int command_intput_fd, int command_output_fd, int command_error_fd, char *cmd_args){
    pid_t pid = fork ();
    if (pid < 0) {
        abort(); 
    } 
    else if (pid == 0){
        dup2 (command_intput_fd, 0); 
        dup2 (command_output_fd, 1); 
        dup2 (command_error_fd, 2);
            // close input_fd, outputfd, error_fd 
        close (fd_table[starting_fd_number]); 
        close (fd_table[starting_fd_number+1]); 
        close (fd_table[starting_fd_number+2]); 

        int execvp_output = execvp (*cmd_args, cmd_args);
        if (execvp_output == -1){
            fprintf (stderr, "Error with execvp %s", strerror(errno));
        } 

    }
    else if (pid > 0) {
            //printf("none of the above \n");
           // printf ("pid is %d \n", pid);                         
        } 
}
                    

int main(int argc, char **argv) {
    int ret, ret2;
    char buf[1024];
    int c;
    // default input_fd numbers
    int input_fd; /*
    int output_fd = 1;
    int error_fd = 2; */
    int tracker = 1; 
    int new_fd; 
    
    int fd_table_counter = 0;
    bool verbose_flag = false;
    bool exit_one = false;  

    while (1){

        int option_index = 0;
        c = getopt_long(argc, argv, "abc:d:f", long_options, &option_index);
        //bool valid_command = false; 

        switch (c){
            case 'R': {
               // valid_command = true; 
                // printf ("inside rdonly \n");
                if (verbose_flag == true){
                    printf ("--%s %s \n", long_options[option_index].name , optarg); 
                    }
                //printf ("optarg is: %s \n", optarg);
                input_fd = open (optarg, O_RDONLY, 0644);
                //printf ("inputfd is: %d \n", input_fd); 
                if (input_fd == -1 ){
                    fprintf (stderr, "Cannot Open the Specified Input File %c \n", optarg);
                    exit_one = true; 
                    }  
                fd_table[fd_table_counter] = input_fd;  
                fd_table_counter++;
                //printf ("optind is: %d \n", optind); 
                break;  
            }  
            case 'B':
               // valid_command = true; 

                if (verbose_flag == true){
                    printf ("--%s %s \n", long_options[option_index].name , optarg); 
                    }
                input_fd = open (optarg, O_RDWR, 0644); 
                if (input_fd == -1){       
                    fprintf (stderr, "Cannot Open the Specified Input File %c \n", optarg);
                    exit_one = true; 
                    }  
                fd_table[fd_table_counter] = input_fd;
                fd_table_counter++;
                break; 
            case 'V':
                //valid_command = true; 
                verbose_flag = true; 
                break; 
            case 'C': {
                //valid_command = true; 
                //printf ("in command %d \n", optarg);

                char v_str[100];
                static char long_option_name[100]; 
                long_option_name[0] =  long_options[option_index].name; 

                if (verbose_flag == true){
                    strcpy (v_str, long_option_name[0]);
                    strcat (v_str, " "); 
                    int index_counter_copy = optind; 
                    while (index_counter_copy < argc) {
                        if (argv[index_counter_copy][0] == '-') {
                            if (argv[index_counter_copy] [1] == '-') {
                            break; 
                            } 
                        }
                        else {
                            strcat(v_str, argv[index_counter_copy]); 
                            strcat (v_str, " "); 

                        } 
                        index_counter_copy++; 
                    }

                    printf ("--%s \n", v_str); 
                }

                parse_command_option (optind, argv, argc, fd_table_counter, starting_fd_number);
                break; 
            }
            case '?': 
                fprintf (stderr, "Invalid Command Passed");
                exit (1); 
                break; 
            default: 
                break; // close case 'C'
        } // close switch
       /* if (valid_command == false) {
            fprintf (stderr, "Invalid Command Passed");
            exit (1); 
            }*/
        if (c == -1){
            break;
            }      
    }  // close while (1)
    // read and write the files
    if (exit_one == true){
        exit(1); 
        }
    exit (0);  
}