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
	else if (head->next == head) 
    { 
        head->next = element; 
		head->prev = element; 
		element->prev = head; 
		element->next = head; 
		//printf ("head only condition \n"); 
        return; 
    }   

	while (element_iterator != head){
		// find the first thing you're bigger than
		//printf ("comparing %s and %s", element->key, element_iterator->key); 
		if (strcmp (element->key, element_iterator->key) >= 0 ) {
			//printf ("inside string cmp if statement \n"); 
			element->prev = element_iterator;
			element->next = element_iterator->next; 
			element_iterator->next = element; 
			element_iterator->next->prev = element; 
			//printf ("inserted %s \n", element_iterator->key); 
			return; 
		} 
		element_iterator = element_iterator->next; 
	}

	/* if (head->next == NULL) 
    { 
        head->next = element; 
		head->prev = element; 
		element->prev = head; 
		element->next = head; 
        return; 
    }   
	while (element_iterator != head){
		// find the first thing you're bigger than
		if (strcmp (element->key, element_iterator->key) >= 0 ) {
			break;   
		} 
		element_iterator = element_iterator->next; 
	}
	element->prev = element_iterator->prev;
	element->next = element_iterator; 
	element_iterator->next = element; 
	element_iterator->next->prev = element; 
	printf ("inserted one! \n"); */

	return; 
}

int SortedList_delete( SortedListElement_t *element) {

	if (opt_yield & DELETE_YIELD) {
		sched_yield();
	}

	// next->prev and prev->next both point to this node
 	if (element->prev->next != element && element->next->prev != element){	
 		return 1;
 	}
 	element->prev->next = element->next; 
	element->next->prev = element->prev; 
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
	/*int counter = 1; 
	SortedListElement_t *head = list;
	SortedListElement_t *element_iterator = head->next; 
	
	if (opt_yield & LOOKUP_YIELD) {
		sched_yield();
	}
	
	printf ("made it before in here\n"); 

	printf ("element_iterator is: %s, head is: %s", element_iterator->key, head->key); 
	while (element_iterator != head){
		printf ("made it in here\n"); 
		++counter; 
		element_iterator = element_iterator->next; 
	}
	return counter;*/

	int counter = 0;
	SortedListElement_t *element_iterator = list->next;  // start at the first real element

	// give up the CPU to another thread before critical section
	if (opt_yield & LOOKUP_YIELD) {
		sched_yield();
	}

	while (element_iterator != list) {
		counter++;
		element_iterator = element_iterator->next;
	}
	return counter;

}
