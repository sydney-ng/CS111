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
    {"rdwr", required_argument, 0, 'B' },
    {"rdonly", required_argument, 0, 'R' },
    {"wronly", required_argument, 0, 'W' },
    {"abort", no_argument, 0, 'A' },
    {"default", required_argument, 0, 'A' },
    {"ignore", required_argument, 0, 'I' },
    {"catch", required_argument, 0, 'N' },
    {"verbose", no_argument, 0, 'V' },
    {"command", no_argument, 0, 'C' },
    {"trunc", no_argument, 0, -1},
    {0, 0, 0, 0}};

int command_intput_fd = 0; 
int command_output_fd = 1; 
int command_error_fd = 2;
int fd_table_counter = 0;
bool exit_one = false;  
bool catch_sig = false; 
bool default_sig = false; 
int catch_sig_int = 0; 
int default_sig_int = 0; 
bool trunc_flag = false; 


int parse_command_option (int optind, char **argv, int argc, int fd_table_counter, int fd_table[100]);
void check_verbose_flag (int option_index, char* optarg, bool verbose_flag); 

int parse_command_option (int optind, char **argv, int argc, int fd_table_counter, int fd_table[100]) {
    //printf ("inside parse_command_option \n"); 
    int num_args = 0; 
    int index_counter = optind; 
    int arr_counter = 0; 
    int command_flag = 0; 
    char *cmd_args[argc]; 
    int temp_fd_table_counter = fd_table_counter - 3;

    while (index_counter < argc) {
        if (argv[index_counter][0] == '-') {
            if (argv[index_counter] [1] == '-') {
            break; 
            }  
        } 
        if (command_flag < 4) {
            // input
            if (command_flag == 0){
                starting_fd_number = fd_table_counter - 3;
                command_intput_fd = fd_table[atoi(argv[index_counter])];
                //fprintf ("command_intput_fd is: %d \n", command_intput_fd); 

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
                //fprintf ("command_output_fd is: %d \n", command_output_fd); 
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
             //fprintf ("command_error_fd is: %d \n", command_error_fd); 

                 if (atoi(argv[index_counter]) >= fd_table_counter) {
                    fprintf (stderr, "File Descriptor for reading contents is wrong");
                    exit (1); 
                }
                command_flag ++; 
                temp_fd_table_counter++;
                } 
            // actual command 
            else if (command_flag == 3) {
                command_flag ++; 
                cmd_args[arr_counter] = argv[index_counter]; 
                arr_counter ++;
            } 
        }// close: else if (command_flag < 4)
        else {
            cmd_args[arr_counter] = argv[index_counter]; 
            num_args ++; 
            //printf ("adding to cmd_arg is: %s \n", argv[index_counter]); 
            arr_counter++; 
            }
            //printf ("counter is now : %d and argc is : %d \n", index_counter, argc);
            index_counter++; 
    //command_to_children (command_intput_fd, command_output_fd, command_error_fd, cmd_args);
}
    cmd_args[arr_counter] = NULL;
    // no command given 
    if (arr_counter < 1) {
        fprintf (1, "--command has no commands, error: %s");
    }

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
    return num_args + 4; // 4 is for 3 fd and the cmd name
}

                    
void file_opening_options (char *option_name, bool verbose_flag, int option_index, char* optarg) {
    check_verbose_flag (option_index, optarg, verbose_flag); 
    int input_fd = open (optarg, option_name, 0644);
    if (input_fd == -1 ){
        fprintf (stderr, "Cannot Open the Specified Input File %s \n", optarg);
        exit_one = true; 
        }  
    fd_table[fd_table_counter] = input_fd; 
    //printf ("fd_table_counter %d || fd_table[fd_table_counter]: %d || input_fd: %d \n", fd_table_counter, fd_table[fd_table_counter], input_fd
      //  ); 
    fd_table_counter++;
}


void check_verbose_flag (int option_index, char* optarg, bool verbose_flag){
    if (verbose_flag == true){
        printf ("--%s %s \n", long_options[option_index].name , optarg); 
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
//    int tracker = 1;
    int new_fd; 
    bool verbose_flag = false;
    while (1){
        //printf ("here at the top of while (1)\n"); 
        int option_index = 0;
        c = getopt_long(argc, argv, "abc:d:f", long_options, &option_index);
        //bool valid_command = false; 

        switch (c){
            case 'R':
                check_verbose_flag (option_index, optarg, verbose_flag);
                file_opening_options (O_RDONLY, verbose_flag, option_index, optarg); 
                break;  
             case 'A':
                check_verbose_flag (option_index, optarg, verbose_flag); 
                raise(SIGSEGV); 
                exit(1); 
                break;  
            case 'W':
                check_verbose_flag (option_index, optarg, verbose_flag);
                file_opening_options (O_WRONLY, verbose_flag, option_index, optarg); 
                break; 
            case 'B':
                check_verbose_flag (option_index, optarg, verbose_flag);
                file_opening_options (O_RDWR, verbose_flag, option_index, optarg); 
                break; 
            case 'V':
                check_verbose_flag (option_index, optarg, verbose_flag);
                printf ("--%s %s \n", long_options[option_index].name , optarg); 
                verbose_flag = true; 
                break; 
            case 'N':
                check_verbose_flag (option_index, optarg, verbose_flag); 
                catch_sig = true; 
                catch_sig_int = atoi(optarg);
                break; 
            case 'I':
                check_verbose_flag (option_index, optarg, verbose_flag); 
                catch_sig = false; 
                break; 
            case 'D':
                check_verbose_flag (option_index, optarg, verbose_flag); 
                default_sig_int = atoi(optarg);
                break; 
            case 'C': {
                char v_str[100];
                static char long_option_name[100]; 
                if (verbose_flag == true){
                    strcpy (v_str, long_options[option_index].name);
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

                int parse_command_option_ret = parse_command_option (optind, argv, argc, fd_table_counter, fd_table);
                optind += parse_command_option_ret; 
                break; 
            }
            case '?': 
                fprintf (stderr, "Invalid Command Passed");
                exit (1); 
                break; 
            default: 
                break; // close case 'C'
        } 
        if (c == -1){
            break;
            }      
    }  // close while (1)
    // read and write the files

    //check if we're handling signals 
    if (catch_sig == true){
        fprintf (stderr, "Exited with Error %d", catch_sig_int); 
        exit (catch_sig_int); 
    }
    else if (default_sig == true) {
        signal(default_sig_int, SIG_DFL); 

    }

    if (exit_one == true){
        exit(1); 
        }
    exit (0);  
}
