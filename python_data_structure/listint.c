#include "stdlib.h"
#include "stdio.h"
#include "listint.h"

void ListInt_print(ListInt * self) {
    if (self->list == NULL) {
        return;
    } else {
        int ** ptr = self->list;
        for (int i = 0; i < self->length; i++) {
            if (ptr[i] != NULL) {
                printf("%d\n", *ptr[i]);
            };
        };
    };
};

void ListInt_append(ListInt * self, int * item) {
    if (self->list == NULL) { // uninitialized list
        int ** ptr;
        ptr = malloc(sizeof(int *));
        self->list = ptr;
        ptr[0] = item;
        self->length = 1;
        return;
    } else if (item != NULL) {
        int ** list_tmp; // temp list for realloc
        uint32_t new_size = self->length + 1;
        int ** ptr;
        if ((list_tmp = realloc(self->list, sizeof(int *) * new_size)) == NULL) {
            return;
        };
        self->list = list_tmp;
        list_tmp[new_size - 1] = item;
        // list_tmp[new_size] = item;
        self->length = new_size;
        return;
    };
    return;
};

void ListInt_extend(ListInt * self, ListInt * list_extend) {
    // Copy over items from the other list
    if (self->list == NULL) {
        self->list = list_extend->list;
    } else if (list_extend->list != NULL) {
        int ** list_tmp;
        uint32_t new_size = self->length + list_extend->length;
        if ((list_tmp = realloc(self, sizeof(int *) * new_size)) == NULL) {
            return;
        };
        self->list = list_tmp;

        int ** extended = list_extend->list;
        // for (int i = self->length; i < new_size; i++) {
        //     // int * value = malloc(sizeof(int)); // allocate new memory for storing extented memory
        //     // *value = *extended[i - self->length];
        //     list_tmp[i] = extended[i - self->length];
        // };
        // self->length = new_size;
    };
};