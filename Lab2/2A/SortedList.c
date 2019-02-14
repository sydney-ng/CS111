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

void SortedList_insert(SortedList_t *list, SortedListElement_t *element) {
	SortedList_t *head = list;
	//printf ("inside insert! \n"); 
	SortedListElement_t *element_iterator = head->next; 

	if (opt_yield & INSERT_YIELD) {
		sched_yield();
	}

	//printf("helooo\n"); 
	//if there's nothing in the linked list 
	if (list == NULL){
		//printf ("null condition \n"); 
		list = element; 
		return; 
	}
	// if the head is the only thing there 
	/*else if (head->next == head) 
    { 
        head->next = element; 
		head->prev = element; 
		element->prev = head; 
		element->next = head; 
		printf ("head only condition \n"); 
        return; 
    }   */

	while (element_iterator != head){
		// find the first thing you're bigger than
		//printf ("comparing %s and %s", element->key, element_iterator->key); 
		if (strcmp (element_iterator->key, element->key) >= 0 ) {
		element->prev = element_iterator->prev;
			element->next = element_iterator; 
			element_iterator->next = element; 	
			element_iterator->next->prev = element; 	
			//printf ("inserted %s \n", element_iterator->key);	
		break;
		} 
		element_iterator = element_iterator->next; 
	}

	return; 
}

int SortedList_delete( SortedListElement_t *element) {

 	if (element->prev->next != element && element->next->prev != element){	
 		return 1;
 	}

 	if (opt_yield & DELETE_YIELD) {
		sched_yield();
	}
	
	element->next->prev = element->prev; 
 	element->prev->next = element->next; 
	free (element); 
	return 0;  
}

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key) {
	SortedList_t *head = list;
	SortedListElement_t *element_iterator = list->next; 

	if (opt_yield & LOOKUP_YIELD) {
		sched_yield();
	}

	while (element_iterator->key != NULL){
		if (strcmp (element_iterator->key, key) == 0){
			return element_iterator;
		}
		element_iterator = element_iterator->next; 
	}
	return NULL; 
}

int SortedList_length(SortedList_t *list){
	//printf ("made it to the beginning of the length fx\n"); 

	int counter = 0;
	SortedListElement_t *element_iterator = list->next;

	if (opt_yield & LOOKUP_YIELD) {
		sched_yield();
	}

	while (element_iterator != list) {
		//printf ("we are here in the whil lloop\n");
		counter++;
		element_iterator = element_iterator->next;
	}
	//printf ("finished counting length \n"); 
	return counter;

}
