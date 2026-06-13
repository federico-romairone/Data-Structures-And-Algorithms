#!/bin/bash
gcc 01_Array/Array_test.c 01_Array/Array.c Item.c -g -o Array_test 
valgrind --leak-check=full ./Array_test