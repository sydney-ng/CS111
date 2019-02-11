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
	SortedListElement_t element_iterator = list->next; 

	if (opt_yield & INSERT_YIELD) {
		sched_yield();
	}

	while (element_iterator->key != NULL){
		// find the first thing you're bigger than
		if (strcmp (element->key, element_iterator->key) > 0 ) {
			element->prev = element_iterator;
			element->next = element_iterator->next; 
			element_iterator->next = element; 
			element_iterator->next->prev = element; 
			return; 
		} 
		element_iterator = element_iterator->next; 
	}

	// if the head is the only thing there 
	head->next = element; 
	head->prev = element; 
	element->prev = head; 
	element->next = head; 
	return; 
}

int SortedList_delete( SortedListElement_t *element) {
	SortedList_t *head = list;
	SortedListElement_t element_iterator = list->next; 

	if (opt_yield & DELETE_YIELD) {
		sched_yield();
	}
	while (element_iterator->key != NULL){
		if (strcmp (element->key, element_iterator->key) == 0){
			element_iterator->prev->next = element_iterator->next; 
			element_iterator->next->prev = element_iterator->prev; 
			free(element_iterator); 
			return 0; 
		}
		element_iterator = element_iterator->next; 
	}
	return 1;
}

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key) {
	SortedList_t *head = list;
	SortedListElement_t element_iterator = list->next; 

	if (opt_yield & LOOKUP_YIELD) {
		sched_yield();
	}

	while (element_iterator->key != NULL){
		if (strcmp (element->key, key) == 0){
			return element;
		}
		element_iterator = element_iterator->next; 
	}
	return NULL; 
}

int SortedList_length(SortedList_t *list){
	counter = 1; 
	SortedList_t *head = list;
	SortedListElement_t element_iterator = list->next; 

	if (opt_yield & LOOKUP_YIELD) {
		sched_yield();
	}

	while (element_iterator->key != NULL){
		counter ++; 
		element_iterator = element_iterator->next; 
	}
	return counter; 
}
