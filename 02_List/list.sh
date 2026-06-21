#!/bin/bash
gcc List_test.c List.c ../Item.c -g -o List_test
valgrind --leak-check=full ./List_test
