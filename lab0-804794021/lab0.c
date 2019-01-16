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

void cause_segFault();
int main(int argc, char **argv) {
        int ret, ret2;
        char buf[1024];
        int c;
        // default FD numbers
        int input_filetype = 0;
        int output_filetype = 1;
    bool causeSegfault = false;
    bool Segfault_msg = false;  
    bool dc = false; 
    int tracker = 1; 
    while (1){
    	static struct option long_options[] = {
        {"input", required_argument, 0, 'I' },
        {"output", required_argument, 0, 'O'},
        {"segfault", no_argument, 0, 'S'},
        {"catch", no_argument, 0, 'C'},
        {"dump-core", no_argument, 0, 'D'},
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
		case 'I': break; 
		case 'O': break; 
		case 'S': break; 
		case 'C': break; 
		case 'D': break; 
		default: exit(3); 
	}}

if (tracker==2 && c !=-1){
	
        switch (c){
        
        case 'I': 
            printf ("\n option -c with value `%s'\n", optarg);
            input_filetype = open (optarg, O_RDONLY);
            printf ("input_filetype is: %d ", input_filetype);
            if (input_filetype < 0 ){
                fprintf (stderr, "Cannot Open the Specified Input File %s", optarg);
                exit (1);
            }
            break; 
     	 case 'S': 
	    causeSegfault = true;		
            /*cause_segFault();
            fprintf (stderr, "Segmentation Fault");
            exit (139);*/
            break; 
        case 'O':
	    //attempt to create the file 
            output_filetype = creat (optarg, S_IRWXU);
            printf ("out_filetype is: %d ", output_filetype);
	    //if it exists, try truncating
	    if (output_filetype == -1) {
 	    printf ("trying to truncate %s", optarg); 
	    output_filetype = truncate (optarg, 0);}
	    //output_filetype = open (optarg, O_TRUNC);}
	    // if it's still an error, exit out  
            if (output_filetype == -1){
 		fprintf (stderr, "%s%s", "Cannot Create and Use Output File ", strerror(errno));
                exit (2);
            }
            break; 
        case 'C': 
	    Segfault_msg = true; 
            break; 
	case'D': 
            Segfault_msg = false;
	    dc = true; 
	    break;  
        default:
            abort (); }//close switch 
}//close if for tracker 2 c -1 

   // read and write the files
    if (c== -1 && tracker == 2){
    
    // account for SegFault being true 
    	if (Segfault_msg == true) {
	   signal(SIGSEGV, cause_segFault); 
	   fprintf (stderr, "%s", "Segmentation Fault Caught"); 
	   exit (4); 
	}
	else if (causeSegfault == true) {
	   cause_segFault(); 
	   fprintf (stderr, "Segmentation Fault %s", strerror(errno)); 
	   if (dc == true) {
	   exit (139); }
	   else {exit(4);}
	}    
	int fd; 
	fd = dup(input_filetype);     
	while ((ret = read(fd, buf, sizeof(buf)-1)) != 0){ //&& ((ret = read(fd, buf, sizeof(buf)-1)) >0)) {
	 (ret2 = write(output_filetype, buf, ret));
	
        }
        if (ret == -1 || ret2 ==-1){
            close (fd); 
	    close (input_filetype); 
 	    close (output_filetype);
	    printf ("exit wrong at the end");
            exit (3);
        }
        else {
            close(input_filetype);
	    close (fd); 
  	    close (output_filetype); 
            // default exit status if everything is correct
            exit (0);
   }
 }}
    return 0;
}

void cause_segFault(){
    char *a = NULL;
    char x = *a;
    x = x + 'f'; 
    exit (139);  
} 
