#include "stdio.h"
#include "stdlib.h"
#include "listint.h"

void main() {
    ListInt * mlist1 = malloc(sizeof(ListInt));
    ListInt * mlist2 = malloc(sizeof(ListInt));
    // ListInt mlist1;
    // ListInt mlist2;
    int a = 10;
    int b = 9;
    int c = -10;
    int d = 20;
    int e = 30;
    int f = 40;

    printf("mlist1.list address %p\n", mlist1->list);
    printf("mlist2.list address %p\n", mlist2->list);
    printf("mlist1.length value %d\n", mlist1->length);
    printf("mlist2.length value %d\n", mlist2->length);
    // printf("mlist1.list address %p\n", mlist1.list);
    // printf("mlist2.list address %p\n", mlist2.list);
    // printf("mlist1.length value %d\n", mlist1.length);
    // printf("mlist2.length value %d\n", mlist2.length);
    
    
    ListInt_append(mlist1, &a);
    ListInt_append(mlist1, &b);
    ListInt_append(mlist1, &c);
    
    ListInt_append(mlist2, &d);
    ListInt_append(mlist2, &e);
    ListInt_append(mlist2, &f);

    ListInt_print(mlist1);
    ListInt_print(mlist2);

    free(mlist1);
    free(mlist2);

}
