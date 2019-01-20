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

int main(int argc, char **argv) {
    int ret, ret2;
    char buf[1024];
    int c;
    // default input_fd numbers
    int input_fd; /*
    int output_fd = 1;
    int error_fd = 2; */
    int tracker = 1; 
    int starting_fd_number = 0;
    int new_fd; 
    
    int fd_table_counter = 0;
    int fd_table[100];
    bool verbose_flag = false;
    int command_intput_fd; 
    int command_output_fd; 
    int command_error_fd; 

    while (1){

    	static struct option long_options[] = {
        {"rdonly", required_argument, 0, 'R' },
        {"wronly", required_argument, 0, 'B' },
        {"verbose", no_argument, 0, 'V' },
        {"command", no_argument, 0, 'C' },
        {0, 0, 0, 0}};

        int option_index = 0;
        c = getopt_long(argc, argv, "abc:d:f", long_options, &option_index);
    	if (c == -1 && tracker == 1){
                tracker = 2;
                optind = 1;
    		continue;  
    	}

    	if (c != -1 && tracker == 1) {
        	switch (c){
                case 'R': break;
                case 'B': break;
                case 'V': break; 
                case 'C': break; 
        		default: exit(1); 
    	   }
        }

        if (tracker==2 && c !=-1){
	
            switch (c){
                case 'R': {
                    // printf ("inside rdonly \n");
                    if (verbose_flag == true){
                        printf ("--%s %s \n", long_options[option_index].name , optarg); 
                        }
                    //printf ("optarg is: %s \n", optarg);
                    input_fd = open (optarg, O_RDONLY, 0644);
                    fd_table[fd_table_counter] = input_fd;  
                    fd_table_counter++;
                    //printf ("inputfd is: %d \n", input_fd); 
                    if (input_fd < 0 ){
                        fprintf (stderr, "Cannot Open the Specified Input File %c \n", optarg);
                        exit (1);
                        }  
                    //printf ("optind is: %d \n", optind); 
                    break;  

                }
                    
                case 'B':
                    if (verbose_flag == true){
                        printf ("--%s %s \n", long_options[option_index].name , optarg); 
                        }
                    input_fd = open (optarg, O_RDWR, 0644); 
                    fd_table[fd_table_counter] = input_fd;
                    fd_table_counter++;
                    if (input_fd < 0 ){       
                        fprintf (stderr, "Cannot Open the Specified Input File %c \n", optarg);
                        exit (1);
                        }  
                    break; 
                case 'V':
                    verbose_flag = true; 
                    break; 
                case 'C': {
                    //printf ("in command %d \n", optarg);

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
                                    temp_fd_table_counter++;
                                    command_flag ++; 
                                    }
                                // output
                                else if (command_flag == 1){
                                    command_output_fd = fd_table[atoi(argv[index_counter])]; 
                                    command_flag ++; 
                                    temp_fd_table_counter++;
                                    }
                                // error 
                                else if (command_flag == 2){
                                    command_error_fd = fd_table[atoi(argv[index_counter])];  
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
                    //printf ("here now \n"); 
                    cmd_args[arr_counter] = NULL;

                    /*int i; 
                    for(i = 0; cmd_args[i] != '\0'; i++){
                        printf("cmd_args[%d] is :%s \n", i, cmd_args[i]);
                    } 
                    for(i = 0; cmd_name[i] != '\0'; i++){
                        printf("cmd_args[%d] is :%s \n", i, cmd_name[i]);
                    } */

                    pid_t pid = fork ();
                    //printf ("after fork \n"); 
                    // check if unsuccessful 
                    if (pid < 0) {
                        //printf ("not successful \n"); 
                        abort(); 
                    } 
                    // successful fork 
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
                    break; 
                }

            }
        } // if statement 
        // read and write the files
        if (c== -1 && tracker == 2){
            exit (0); 
       
        }   
    }
return 0; 
}
