#!bin/bash
make -B
gcc test_pystruct.c -L. -lpystruct -o test_pystruct.o