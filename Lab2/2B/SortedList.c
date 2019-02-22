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
    SortedList_t *element_iterator = list->next;

    if (opt_yield & INSERT_YIELD) {
        sched_yield();
    }
    while (element_iterator != list) {
        if (strcmp(element_iterator->key,element->key) >= 0) {
             element->prev = element_iterator->prev;
            element->next = element_iterator;
            element_iterator->prev->next = element;
            element_iterator->prev = element;
            return;  
        }
        else {
            element_iterator = element_iterator->next;
        }
    }
   
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
        if (element_iterator->next->prev != element_iterator) {
            return -1; 
        }
        else if (element_iterator->prev->next != element_iterator){
            return -1; 
        }
        counter++;
        element_iterator = element_iterator->next;
    }
    
    //printf ("finished counting length \n");
    return counter;
    
}

