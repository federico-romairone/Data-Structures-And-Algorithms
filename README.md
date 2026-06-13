# How to Compile and Run Tests

## Using GCC (Command Line)

### Compile and run tests:
```bash
gcc 01_Array/Array_test.c 01_Array/Array.c Item.c -g -o Array_test 
./Array_test
```

### With memory leak detection (requires valgrind):
```bash
gcc 01_Array/Array_test.c 01_Array/Array.c Item.c -g -o Array_test 
valgrind --leak-check=full ./Array_test
```