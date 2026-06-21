#!/bin/bash
gcc Array_test.c Array.c ../Item.c -g -o Array_test 
valgrind --leak-check=full ./Array_test