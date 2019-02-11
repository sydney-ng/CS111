#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include <sys/resource.h>
#include <sched.h>
#include "SortedList.h"

int opt_yield = 0; 
int num_threads = 1;
int num_iterations = 1;
SortedListElement_t **original_list;
SortedList_t *linked_l;
struct timespec start_time;
struct timespec end_time;
pthread_mutex_t m_lock = PTHREAD_MUTEX_INITIALIZER;
volatile int s_lock = 0;
int num_total;  
char lockflag_type[5]; 
char yieldopts[4]; 
bool mutex_flag = false; 
bool spinlock_flag = false; 

static struct option long_options[] = {
    {"threads", required_argument, 0, 'T' },
    {"iterations", required_argument, 0, 'I' },
    {"yield", required_argument, 0, 'Y' },
    {"sync", required_argument, 0, 'S' },
    {0, 0, 0, 0}
};

void *linked_l_handler(void *vargp);
void createList(); 
void printdata(); 


/* printing: the name of the test, which is of the form: list-yieldopts-syncopts: where
yieldopts = {none, i,d,l,id,il,dl,idl}
syncopts = {none,s,m}
the number of threads (from --threads=)
the number of iterations (from --iterations=)
the number of lists (always 1 in this project)
the total number of operations performed: threads x iterations x 3 (insert + lookup + delete)
the total run time (in nanoseconds) for all threads
the average time per operation (in nanoseconds).*/ 

void printdata() {
	int num_operations_performed = num_threads * num_iterations * 3;
	long total_run_time = ((long)end_time.tv_sec - (long)start_time.tv_sec)*1000000000 + ((long)end_time.tv_nsec - (long)start_time.tv_nsec);  
	long average_time_per_operation = total_run_time/num_operations_performed; 
	

	FILE * fp = fopen ("lab2_add.csv" , "w+ ");
	fprintf (fp, "%s, %s, %d, %d, 1, %d, %ld, %ld \n", yieldopts, lockflag_type, num_threads, num_iterations, num_operations_performed, total_run_time, average_time_per_operation); 

}
void createList(){
    num_total = num_threads * num_iterations;
	linked_l = malloc(sizeof(SortedList_t));
	linked_l->next = linked_l;
	linked_l->prev = linked_l;
	linked_l->key = NULL;	
	printf ("createList num_total is: %d\n", num_total); 

	int counter =0; 
	original_list = malloc(num_total * sizeof(SortedListElement_t*));
 	int i; 
	int char_len = 3; 
	const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int num_total_temp = num_total; 

	while (num_total_temp !=0) {

			original_list[counter] = malloc(sizeof(SortedListElement_t));
			original_list[counter]->prev = NULL;
			original_list[counter]->next = NULL; 
			char alphakey [4]; 
			for (i = 0; i < 3; i++){
				int alpha_num = rand() % (int) (sizeof alphabet - 1);
				alphakey[i] = alphabet[alpha_num];
			}
			alphakey[3] = '\0';
			original_list[counter]->key = alphakey; 
			
		counter ++; 
		num_total_temp--; 
	}
}

void *linked_l_handler(void *vargp) {

	printf ("here in linked_l_handler \n"); 
	int t_ID = *((int *) vargp); 
	int temp_thread_ID = t_ID; 
	printf ("threadID is: %d \n", t_ID); 
	printf ("num_total is: %d\n", num_total); 

	for (temp_thread_ID; temp_thread_ID < num_total; temp_thread_ID += num_threads) {
		SortedList_insert(linked_l, original_list[temp_thread_ID]);
	}


	// gets the list length
	/*int linked_l_len; 
	linked_l_len = SortedList_length(linked_l);

	temp_thread_ID = threadID; 
	SortedListElement_t *found_element; 
	SortedListElement_t *find_me;  
	while (temp_thread_ID < num_total) {
		find_me = original_list[temp_thread_ID]; 
		found_element = SortedList_lookup (linked_l, find_me->key); 
		if (found_element != NULL){
			SortedList_delete (found_element); 
		}
	} 
	pthread_exit(NULL); */
}

void set_flags(char* optarg){ 
	char m = 'm';
	char s = 's'; 
	char *m_pointer = &m; 
	char *s_pointer = &s; 

    if (strcmp(optarg, m_pointer) == 0){
        mutex_flag = true; 
        lockflag_type[0] = 'm'; 
        lockflag_type[1] = '\0'; 

    }

    else if (strcmp(optarg, s_pointer) == 0){
        spinlock_flag = true; 
        lockflag_type[0] = 's';  
   	    lockflag_type[1] = '\0'; 
  
    }
    else {
    	lockflag_type[0]= 'n';
    	lockflag_type[1] = 'o'; 
    	lockflag_type[2] = 'n'; 
    	lockflag_type[3] = 'e'; 
    	lockflag_type[4] = '\0'; 
    }
} 

int main (int argc, char **argv) {
	int c; 
    int i; 

	while (1)
    {
        int option_index = 0;
        c = getopt_long(argc, argv, "abc:d:f", long_options, &option_index);
        
        if (c == -1) {
            break;
        }
        switch (c){
            case 'T':
                if (optarg) {
                    num_threads = atoi(optarg);
                }
                break;
            case 'S':
                set_flags(optarg); 
                break;
            case 'I':
                if (optarg) {
                    num_iterations = atoi(optarg);
                }
                break;
            case 'Y':
                if (optarg) {
                	int num_optarg_chars; 
                	int pos_counter = 0; 
                	num_optarg_chars = strlen(optarg); 
                	while (pos_counter != num_optarg_chars) {
                		yieldopts[pos_counter] = optarg[pos_counter]; 
                		
                		if (optarg[pos_counter] == 'i'){
                			opt_yield = opt_yield | INSERT_YIELD; 
                		}
                		else if (optarg[pos_counter] == 'd'){
                		    opt_yield = opt_yield | DELETE_YIELD; 

						}
                		else if (optarg[pos_counter] == 'l'){
                		    opt_yield = opt_yield | LOOKUP_YIELD; 
						}
                		pos_counter++; 
                	}
                }

                break;
            case '?':
                fprintf (stderr, "bogus args \n");
                fflush(stderr);
                exit (1); 
                break; 
            default:
                exit (1);
        }
    }
    createList();
    clock_gettime(CLOCK_MONOTONIC, &start_time); //monotonic isn't affected by discountinued jobs

	pthread_t *add_thread = malloc((sizeof(pthread_t)*num_threads)); 

	int *arg = malloc(sizeof(*arg));


    for (i=0; i < num_threads; i++){
    	*arg = i;
  		printf ("before, num_total is: %d\n", num_total); 

        pthread_create(&add_thread[i], NULL, linked_l_handler, (void*) (arg));
    }
    
    for (i =0; i < num_threads; i++){
        pthread_join(add_thread[i], (void**)NULL);
    }

    // checks the length of the list to confirm that it is zero
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    /*if (SortedList_length(linked_l) != 0) {
    	fprintf(stderr, "Length of List After Computation is not 0"); 
    }*/

    printdata(); 
    
}