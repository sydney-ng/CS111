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
#define _GNU_SOURCE   

int fd_table[100];
int starting_fd_number = 0;
int command_intput_fd = 0;
int command_output_fd = 1;
int command_error_fd = 2;
int fd_table_counter = 0;
bool exit_one = false;
bool catch_sig = false;
bool default_sig = false;
int catch_sig_int = 0;
int default_sig_int = 0;
static int append_flag = 0;
static int cloexec_flag = 0;
static int creat_flag = 0;
static int directory_flag = 0;
static int dysnc_flag = 0;
static int excl_flag = 0;
static int nofollow_flag = 0;
static int nonblock_flag = 0;
static int rsync_flag = 0;
static int sync_flag = 0;
static int trunc_flag = 0;
static int dsync_flag = 0; 

int pass_flags;

static struct option long_options[] = {
    {"rdwr", required_argument, 0, 'B' },
    {"close", required_argument, 0, 'E' },
    {"rdonly", required_argument, 0, 'R' },
    {"wronly", required_argument, 0, 'W' },
    {"abort", no_argument, 0, 'A' },
    {"default", required_argument, 0, 'D' },
    {"ignore", required_argument, 0, 'I' },
    {"catch", required_argument, 0, 'N' },
    {"verbose", no_argument, 0, 'V' },
    {"command", no_argument, 0, 'C' },
    {"pipe", no_argument, 0, 'P' },
    {"pause", no_argument, 0, 'S' },
    {"append",  no_argument, &append_flag, -1},
    {"cloexec",  no_argument, &cloexec_flag, -1},
    {"creat",  no_argument, &creat_flag, -1},
    {"directory",  no_argument, &directory_flag, -1},
    {"dsync",  no_argument, &dsync_flag, -1},
    {"excl",  no_argument, &excl_flag, -1},
    {"nofollow",  no_argument, &nofollow_flag, -1},
    {"nonblock",  no_argument, &nonblock_flag, -1},
    {"rsync",  no_argument, &rsync_flag, -1},
    {"sync",  no_argument, &sync_flag, -1},
    {"trunc",  no_argument, &trunc_flag, -1},
    {0, 0, 0, 0}};

int create_flags (int original_flag); 
void reset_flags (); 

int parse_command_option (int optind, char **argv, int argc, int fd_table_counter, int fd_table[100]);
void check_verbose_flag (int option_index, char* optarg, bool verbose_flag);
void file_opening_options (int option_name, bool verbose_flag, int option_index, char* optarg);

int parse_command_option (int optind, char **argv, int argc, int fd_table_counter, int fd_table[100]) {
    int num_args = 0;
    int index_counter = optind;
    int arr_counter = 0;
    int command_flag = 0;
    char *cmd_args[argc];
    int temp_fd_table_counter = fd_table_counter - 3;
    int input_index = 0; 
    int output_index = 0; 
    int err_index = 0; 
    
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
                input_index = atoi(argv[index_counter]); 
                if (atoi(argv[index_counter]) >= fd_table_counter || command_intput_fd == -1) {
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
                if (atoi(argv[index_counter]) >= fd_table_counter || command_output_fd == -1) {
                    fprintf (stderr, "File Descriptor for writing contents is wrong");
                    exit (1);
                    
                }
                output_index = atoi(argv[index_counter]); 
                command_flag ++;
                temp_fd_table_counter++;
            }
            // error
            else if (command_flag == 2){
                
                command_error_fd = fd_table[atoi(argv[index_counter])];
                //fprintf ("command_error_fd is: %d \n", command_error_fd);
                
                if (atoi(argv[index_counter]) >= fd_table_counter || command_error_fd == -1) {
                    fprintf (stderr, "File Descriptor for reading contents is wrong");
                    exit (1);
                }
                err_index = atoi(argv[index_counter]); 
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
        fprintf (stderr, "--command has no commands, error");
        exit_one = true;
        return num_args;
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
        int i;

        for ( i = 3; i < fd_table_counter; i++){
            if (fd_table[i] != -1){
                close (i);
            }
        }

        for (i = 0; i < 3; i++){
            if (fd_table[starting_fd_number] != -1) {
                close (fd_table[starting_fd_number]);
            }
            starting_fd_number++; 
        }
        
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


void file_opening_options (int option_name, bool verbose_flag, int option_index, char* optarg) {
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

void sigHandler (int optarg) {
    fprintf (stderr, "%d caught \n", optarg); 
    exit (optarg); 
}

int create_flags (int original_flag){

    int actual_flag; 
    actual_flag =
    (append_flag & O_APPEND) |
    (cloexec_flag & O_CLOEXEC) |
    (creat_flag & O_CREAT) |
    (directory_flag & O_DIRECTORY) |
    (dsync_flag & O_DSYNC) |
    (excl_flag & O_EXCL) |
    (nofollow_flag & O_NOFOLLOW) |
    (nonblock_flag & O_NONBLOCK) |
    (rsync_flag & O_RSYNC) |
    (sync_flag & O_SYNC) |
    (trunc_flag & O_TRUNC) | (original_flag);
    return actual_flag; 
}

void reset_flags () {
   append_flag = 0;
   cloexec_flag = 0;
   creat_flag = 0;
   directory_flag = 0;
   dysnc_flag = 0;
   excl_flag = 0;
   nofollow_flag = 0;
   nonblock_flag = 0;
   rsync_flag = 0;
   sync_flag = 0;
   trunc_flag = 0; 
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
            case 'E':
                close (fd_table[atoi(optarg)]);
                fd_table[atoi(optarg)] = -1; 
                break;
            case 'R':
                pass_flags = create_flags (O_RDONLY);
                file_opening_options (pass_flags, verbose_flag, option_index, optarg);
                reset_flags (); 
                break;
            case 'A':
                if (verbose_flag == true) {
                    fprintf(stdout, "--abort \n" );
                }
                //check_verbose_flag (option_index, optarg, verbose_flag);
                raise(SIGSEGV);
                exit (139); 
                break;
            case 'W':
                pass_flags = create_flags (O_WRONLY);
                file_opening_options (pass_flags, verbose_flag, option_index, optarg);
                reset_flags (); 
                break;
            case 'B':
                pass_flags = create_flags (O_RDWR);
                file_opening_options (pass_flags, verbose_flag, option_index, optarg);
                reset_flags (); 
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
                signal(catch_sig_int, sigHandler); 
                break;
            case 'P':
                check_verbose_flag (option_index, optarg, verbose_flag);
                int pipefd[2];
                int pipe_output;
                pipe_output = pipe(pipefd); 
                fd_table[fd_table_counter] = pipefd[0];
                fd_table_counter++;
                fd_table[fd_table_counter] = pipefd[1];
                fd_table_counter++;
                /*else {
                    fd_table[fd_table_counter] = -1;
                    fd_table_counter++;
                    fd_table[fd_table_counter] = -1;
                    fd_table_counter++;
                    exit_one = true; 
                    printf ("ERROR PIPE FAIL\n"); 
                }*/
                break;
            case 'S':
                pause();
                break;
            case 'I':
                check_verbose_flag (option_index, optarg, verbose_flag);
                catch_sig_int = atoi(optarg);
                signal (catch_sig_int, SIG_IGN); 
                break;
            case 'D':
                check_verbose_flag (option_index, optarg, verbose_flag);
                default_sig_int = atoi(optarg);
                signal(default_sig_int, SIG_DFL);
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

    if (exit_one == true){
        exit(1);
    }
    exit (0);
}
