// Underlying mechanism for new.h
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "new.h"
#include "pystruct.r"

void *new(const void *_class, ...) {
    // The new function returns a pointer of the object of the specified _class
    // _class is the pointer to the parent class of the created object
    // _class includes the ctor function that do the mem allocation
    
    const struct Class *class = _class; // Assign and cast the void pointer _class to type of struct class
    void *ptr = calloc(1, class->size); // ptr points to the mem location containing the underlying value of the object
    assert(ptr);
    * (const struct Class **) ptr = class; // ptr contains address of the object obtained through calloc, *ptr contains address of the class

    if (class->_create) {
        va_list args;
        va_start(args, _class);
        ptr = class->_create(ptr, &args);
        va_end(args);
    };
    return ptr;
};

void delete(void *self) {
    const struct Class **ptr = self;
    if (self && *ptr && (*ptr)->_destroy) {
        self = (*ptr)->_destroy(self);
    };
    free(self);
};

void print(void *self, int newline) {
    const struct Class **ptr = self;
    if (self && *ptr && (*ptr)->_str) {
        (*ptr)->_str(self, newline);
    };
};

// Print type of object in humanly readable format
void printType(void *self) {
    struct Class **ptr = self;
    if (ptr && (*ptr)->type) {
        switch ((*ptr)->type) {
            case 0:
                printf("integer");
                break;
            case 1:
                printf("float");
                break;
            case 2:
                printf("string");
                break;
            case 3:
                printf("list");
                break;
            case 4:
                printf("dict");
                break;
        }
    };
};