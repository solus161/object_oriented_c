#include <stdio.h>
#include "new.h"
#include "pystruct.h"

int main(){
    // Create some string
    void * mstring1 = new(String, "Hello there!");
    void * mstring2 = new(String, "General Kenobiiii!");

    printf("String 1: ");
    print(mstring1, 1);
    printf("String 2: ");
    print(mstring2, 1);

    // Compare two strings
    printf("String 1 == String 2 -> %d\n", equal(mstring1, mstring2));

    void *int1 = new(Integer,  9);
    void *int2 = new(Integer, 9);
    printf("Integer 1: ");
    print(int1, 1);
    printf("Integer 2: ");
    print(int2, 1);

    // Compare two numbers
    printf("Integer 1 == Integer 2 -> %d\n", equal(int1, int2));

    void *mlist = new(List);
    append(mlist, mstring1);
    append(mlist, int1);
    append(mlist, mstring2);
    append(mlist, int2);

    printf("List of object: ");
    print(mlist, 0);
    // delete(mstring1);
    // delete(mstring2);
    // delete(int1);
    // delete(int2);

    return 1;
};