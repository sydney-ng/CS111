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
#include <unistd.h>
#include <signal.h>

int main(int argc, char **argv) {
    int ret, ret2;
    char buf[1024];
    int c;
    // default input_fd numbers
    int input_fd = 0;
    int output_fd = 1;
    int error_fd = 2; 
    int tracker = 1; 
    int new_intput_fd = 0; 
    int new_output_fd = 1;
    int new_error_fd = 2; 
    bool verbose_flag = false; 

    while (1){

    	static struct option long_options[] = {
        {"rdonly", required_argument, 0, 'R' },
        {"rdwr", required_argument, 0, 'B' },
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
                case 'R':
                    printf ("inside rdonly \n");
                    if (verbose_flag == true){
                        printf ("--%s %s \n", long_options[option_index].name , optarg); 
                        }
                    printf ("optarg is: %s \n", optarg);
                    input_fd = open (optarg, O_RDONLY, 0644); 
                    printf ("inputfd is: %d \n", input_fd); 
                    if (input_fd < 0 ){
                        fprintf (stderr, "Cannot Open the Specified Input File %c", optarg);
                        exit (1);
                        }  
                    printf ("optind is: %d \n", optind); 
                    break;  
                case 'B':
                    if (verbose_flag == true){
                        printf ("--%s %s \n", long_options[option_index].name , optarg); 
                        }
                    input_fd = open (optarg, O_RDWR); 
                    if (input_fd < 0 ){       
                        fprintf (stderr, "Cannot Open the Specified Input File %c", optarg);
                        exit (1);
                        }  
                    break; 
                case 'V':
                    verbose_flag = true; 
                    break; 
                case 'C':
                    printf ("in command %d \n", optarg);
                    printf ("optind is: %d \n", optind); 
                    int index_counter = optind; 
                    printf ("index counter is: %d \n", index_counter); 
                    printf ("argc is: %d \n", argc); 
                    printf ("argv is: %s \n", argv);
                    int arr_counter = 0; 
                    int command_flag = 0; 
                    char *cmd_args[argc]; 
                    char *cmd_name [100]; 


                    printf ("index counter is: %d and argc is: %d \n" , index_counter, argc); 
                    while (index_counter < argc) {
                            printf ("at top of while loop \n");                           
                            if (argv[index_counter][0] == '-') {
                                if (argv[index_counter] [1] == '-') {
                                break; 
                                }  
                            } 
                            else if (command_flag < 4) {
                                if (command_flag == 0){
                                    new_intput_fd = atoi(argv[index_counter]); 
                                    printf ("new input_fd: %d \n", new_intput_fd); 
                                    command_flag ++; 
                                    }
                                else if (command_flag == 1){
                                    new_output_fd = atoi(argv[index_counter]); 
                                    printf ("new output_fd: %d \n", new_output_fd);                       
                                    command_flag ++; 
                                    }
                                else if (command_flag == 2){
                                    new_error_fd = atoi(argv[index_counter]);  
                                    printf ("new new_error_fd: %d \n", new_error_fd); 
                                    command_flag ++; 
                                    } 
                                else if (command_flag == 3) {
                                    cmd_name [0] = argv[index_counter]; 
                                    printf ("command to execute is: %s \n", cmd_name[0]); 
                                    command_flag ++; 
                                }
                            }
                            else {
                                cmd_args[arr_counter] = argv[index_counter]; 
                                printf ("adding to cmd_arg is: %s \n", argv[index_counter] ); 
                                arr_counter++; 
                                optind = index_counter;
                                }
                            printf ("counter is now : %d and argc is : %d \n", index_counter, argc); 
                            index_counter++; 
                    }
                    printf ("here now \n"); 
                    cmd_args[arr_counter] = '\0'; 

                    pid_t pid = fork ();
                    printf ("after fork \n"); 
                    // check if unsuccessful 
                    if (getpid() < 0) {
                        printf ("not successful \n"); 
                        abort(); 
                    } 
                    // successful fork 
                    else if (getpid() == 0){
                        dup2 (input_fd, new_intput_fd); 
                        dup2 (output_fd, new_output_fd); 
                        dup2 (error_fd, new_error_fd);
                            // close input_fd, outputfd, error_fd 
                        close (input_fd); 
                        close (output_fd); 
                        close (error_fd); 

                        execvp (cmd_name [0], cmd_args); 

                    }
                    else {
                            printf("none of the above \n");
                            printf ("pid is %d \n", pid);                         
                        }

                }
        }
    // read and write the files
    if (c== -1 && tracker == 2){
        exit (0); 
        //else {
            //close (input_fd); 
            //close (output_fd); 
          //  }
   // } 
    }
}
return 0; 
}
                       
         
   // } // end of while loop
//    return 0;
//}


/* 
char **array = malloc(totalstrings * sizeof(char *));

Next you need to allocate space for each string:

int i;
for (i = 0; i < totalstrings; ++i) {
    array[i] = (char *)malloc(stringsize+1);
}
*/
