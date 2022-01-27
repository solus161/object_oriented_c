#include "stdint.h"

#ifndef LISTINT_H
#define LISTINT_H

typedef struct { // simple list of int
    int ** list; // void pointer to the array of pointer
    uint32_t length; // size of the list
} ListInt;

void ListInt_print(ListInt * self);
void ListInt_append(ListInt * self, int * item); // add pointer of an item - pointer to the list
void ListInt_extend(ListInt * self, ListInt * list_extend); // extend current list by another list
void * ListInt_pop(ListInt * self, uint32_t index); // pop out item at index
void * ListInt_index(ListInt * self, int * item); // return the first index of a value

#endif