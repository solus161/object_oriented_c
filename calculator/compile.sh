#!bin/bash
make -B
gcc test_calculator.c -g -L. -lcalculator -o test_calculator.o