#ifndef CLASS_R
#define CLASS_R
#include "stddef.h"
#include "stdio.h"
#include "stdarg.h"
// General Class type
struct Class {
    size_t size; // Size of the object, used when initiate
    int type; // Class description
    void * (* _create) (void * self, va_list * args); // Pointer to function returning void pointer
    void * (* _destroy) (void * self); // Pointer to destroyer function
    void (* _str) (void * self, int newline); // Pointer the print function, print out the value of the object
};
#endif