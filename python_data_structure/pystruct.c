#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "pystruct.h"
#include "new.h"
#include "pystruct.r"

// INTEGER-----------------------------------------------------------------------
// ------------------------------------------------------------------------------
// Integer object
struct Integer {
    const void * class;
    int * value;
};

static void *IntegerCreate(void *_self, va_list *args) {
    struct Integer *self = _self;
    int value = va_arg(*args, int);
    self->value = malloc(sizeof(int));
    assert(self->value);
    *(self->value) = value;
    return self;
};

static void *IntegerDestroy(void *_self) {
    struct Integer *self = _self;
    assert(self->value);
    free(self->value);
    printf("Integer destroyed!");
    return self;
};

static void IntegerPrint(void *_self, int newline) {
    struct Integer *self = _self;
    assert(self->value);
    printf("%d", *(self->value));
    if (newline == 1) {
        printf("\n");
    };
};

static const struct Class classInteger = {
    sizeof(struct Integer), 0, IntegerCreate, IntegerDestroy, IntegerPrint
};

const void * Integer = &classInteger;

// STRING------------------------------------------------------------------------
// ------------------------------------------------------------------------------
// String object
struct String {
    const void * class; // Pointer to the parent class of String
    char * value;    
};

// Constructor of String
static void *StringCreate(void *_self, va_list *args){
    struct String *self = _self;
    const char *value = va_arg(*args, const char *);
    self->value = malloc(strlen(value) + 1);
    assert(self->value);
    strcpy(self->value, value);
    return self;
};

// Destructor of String
static void *StringDestroy(void *_self) {
    struct String *self = _self;
    assert(self->value);
    free(self->value);
    printf("String destroyed!\n");
    return self;
};

// Print value of an object
static void StringPrint(void *_self, int newline) {
    struct String *self = _self;
    assert(self->value);
    printf("'%s'", self->value);
    if (newline == 1) {
        printf("\n");
    };
};

// Detailed description of String class
static const struct Class classString = {
    sizeof(struct String), 2, StringCreate, StringDestroy, StringPrint
};

const void * String = &classString;

// LIST--------------------------------------------------------------------------
// ------------------------------------------------------------------------------
// List object

struct List {
    const void * class;
    int length;
    void ** value;
};

static void * ListCreate(void *_self, va_list *args){
    struct List *self = _self;
    self->length = 0;
    self->value = malloc(sizeof(void *) * 0);
    return self;
};

// Append and object to list
void append(void *_self, void *item) {
    struct List *self = _self;
    self->length++;
    int new_length = self->length + 1;
    void * new_value = realloc(self->value, sizeof(void *) * new_length);
    if (new_value != NULL) {
        self->value = new_value;
        self->value[self->length - 1] = item;
    };
};

static void * ListDestroy(void *_self) {
    struct List *self = _self;
    for (int i; i < self->length; i++) {
        delete(self->value[i]);
    };
    free(self->value);
    return self;
};

static void ListPrint(void *_self) {
    struct List *self = _self;
    void **values = self->value;
    printf("[");
    for (int i; i < self->length; i++) {
        void * item = values[i];
        print(item, 0);
        printf(", ");
    };
    printf("]\n");
};

static const struct Class classList = {
    sizeof(struct List), 3, ListCreate, ListDestroy, ListPrint
};

const void * List = &classList;

// Compare two objects
int equal(void *object0, void *object1) {
    struct Class **ptr0 = object0;
    struct Class **ptr1 = object1;

    if ((*ptr0)->type == (*ptr1)->type) {
        if ((*ptr0)->type == 0) {
            const struct Integer *int0 = object0;
            const struct Integer *int1 = object1;
            if (*(int0->value) == *(int1->value)) {
                return 1;
            } else {
                return 0;
            };
        } else if ((*ptr0)->type == 2) {
            const struct String *string0 = object0;
            const struct String *string1 = object1;
            if (*(string0->value) == *(string1->value)) {
                return 1;
            } else {
                return 0;
            };
        };
    } else {
        return 0;
    };
    return 0;
};