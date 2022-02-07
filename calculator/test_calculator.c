#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "calculator.h"
static const int EXPSIZE = 100;

int main() {
    // 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3
    // 1*5 - 4/3 +2^2
    // (((1 -3)^2)-5^1.1)/(3-7)^1 + 22/2^2
    // (((1 -3)**2)-5**1.1)/(3-7)**1 + 22/2**2
    printf("A simple calculator using shunting yard algorithm.\n");
    printf("by Quang Nguyen @github.com/solus161\n");
    printf("Press q to quit\n");
    printf("__________________________________________________\n");
    
    char expression[EXPSIZE];
    char key_pressed;
    struct Calculator * my_cal = init_calculator();
    double result;
    while (1) {
        fgets(expression, EXPSIZE, stdin);
        if (expression[0] == 'q') break;
        result = compute(my_cal, expression, 0);
        printf("%f\n", result);
    }
};