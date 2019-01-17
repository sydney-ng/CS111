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
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int ret, ret2;
    char buf[1024];
    int c;
    // default FD numbers
    int fd = 0;
    int output_filetype = 1;
    int tracker = 1; 
    bool verbose_flag = false; 

    while (1){

    	static struct option long_options[] = {
        {"rdonly", required_argument, 0, 'R' },
        {"rdwr", required_argument, 0, 'B' },
        {"verbose", no_argument, 0, 'V' },
        {"command", required_argument, 0, 'C' },
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
        		default: exit(3); 
    	   }
        }

        if (tracker==2 && c !=-1){
	
            switch (c){
            
            case 'R':
                if (verbose_flag == true){
                    printf ("--%s %s \n", long_options[option_index].name , optarg); 
                }
                fd = open (optarg, O_RDONLY); 
                if (fd < 0 ){
                    fprintf (stderr, "Cannot Open the Specified Input File %s", optarg);
                    exit (1);
                }  
                break;  
            case 'B':
                if (verbose_flag == true){
                    printf ("--%s %s \n", long_options[option_index].name , optarg); 
                }
                fd = open (optarg, O_RDWR); 
                if (fd < 0 ){       
                    fprintf (stderr, "Cannot Open the Specified Input File %s", optarg);
                    exit (1);
                }  
                break; 
            case 'V':
                verbose_flag = true; 
                break; 
            default:
                abort (); 
            }//close switch 
        }//close if for tracker 2 c -1 

         // read and write the files
        if (c== -1 && tracker == 2){
        	while ((ret = read(fd, buf, sizeof(buf)-1)) != 0){ //&& ((ret = read(fd, buf, sizeof(buf)-1)) >0)) {
        	   (ret2 = write(output_filetype, buf, ret));
        	}
            if (ret == -1 || ret2 ==-1){
                close (fd); 
         	    close (output_filetype);
        	    printf ("exit wrong at the end");
                exit (3);
            }
            else {
                close (fd); 
          	    close (output_filetype); 
                exit (0); // default exit status if everything is correct

            }
        }
    } // end of while loop
    return 0;
}
