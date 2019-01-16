#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <fcntl.h>

int main(int argc, char **argv) {
	bool x = true; 
	int ret, ret2;
	int input_fd = 0;
	int output_fd = 1; 
	char buf[1024];
	int count; 
	int i; 


	while (x == true){
		int c; 
		int option_index = 0;

    	static struct option long_options[] = {
        {"rdonly", required_argument, 0, 'R' },
        {"rdwr", required_argument, 0, 'B' },
        {"command", required_argument, 0, 'C' },
        {0, 0, 0, 0}};
        c = getopt_long(argc, argv, "abc:d:f", long_options, &option_index);
        x = false;

        switch (c){ 
        	case 'C':
		     	printf("here in command"); 
		     	if (argc > 1){
 					for( count = 1; count < argc; count++ )
       					printf("%s", argv[count]);
		     	}
		     	printf("%s", optarg);
		      	break; 
	        case 'R':
		     	printf("here in read"); 
				input_fd = open (optarg, O_RDONLY); 
				if (input_fd < 0 ){
	                fprintf (stderr, "Cannot Open the Specified Input File %s", optarg);
	                exit (1);
	            }  
		     	break;  
		    case 'B':
		    	printf("here in read/write"); 
				input_fd = open (optarg, O_RDWR); 
				if (input_fd < 0 ){
	                fprintf (stderr, "Cannot Open the Specified Input File %s", optarg);
	                exit (1);
	            }  
		     	break; 
		} // close switch

		//do all the reading and writing 
		while ((ret = read(input_fd, buf, sizeof(buf)-1)) != 0){ 
	 		(ret2 = write(output_fd, buf, ret));
        }
        //probem with reading & writing
        if (ret == -1 || ret2 ==-1){
            close (input_fd); 
	    	close (output_fd); 
            exit (3);
        }
        // exit correctly 
        else {
            close(input_fd);
	    	close (output_fd); 
            exit (0); 
        }
	} // close while 
} // close main 