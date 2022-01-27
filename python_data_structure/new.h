#ifndef NEW_H
#define NEW_H

#include <stddef.h>

void * new(const void *class, ...);
void delete(void *self);
void print(void *self, int newline);
void typeOf(void *self);
void printType(void *self);
int equal(void *object0, void *object1);
void append(void *self, void *item);
size_t sizeOf (const void * self);

#endif