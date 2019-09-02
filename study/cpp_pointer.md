# Pointers and memory
## three types of memory
* static/global
* automatic
* dynamic

## how to read a declaration: reading backward
* `const int *pci`: pci is a pointer variable to a constant integer

## display a pointer
* `%x`: display the value as hexadecimal number
* `%o`: display the value as octal number
* `%p`: display the value in an implementation-specific manner; typically as a hexadecimal number

## Pointer to function
* `void (*foo)()`

## concept of null
* null concept
* null pointer constant
* NULL macro
* ASCII NUL
* a null string
* null statement

## pointer to void
* sample representation to pointer to char
* never equal to other pointer. two void pointer assigned to NULL will be equal

## global and static pointer: is initialized to NULL when the program start

## predefined pointer-related types
* `size_t`
* `ptrdiff_t`
* `intptr_t` and `uintptr_t`: store pointer address
* avoid casting pointer to integer

## constants and pointer
* pointers to a constant: cannot use the pointer to modify the value it is referencing. `const int *pci` or `int const *pci`
* const pointers to a nonconstants: pointer cannot be changed, but the data pointed to can be modify. `int *const pci`
* const pointers to a contants: pointer cannot be changed, data point to cannot be changed through pointer. `const int * consant pci`
* pointer to (const pointers to const): `const int * const * pci`

pointer type | pointer modificable | data pointed to modificable
------------ | ------------ | ------------
pointer to nonconstants | :heavy_check_mark: | :heavy_check_mark:
pointer to a constant | :heavy_check_mark: | :heavy_multiplication_x:
constant pointer to a nonconstant | :heavy_multiplication_x: | :heavy_check_mark:
constant pointer to a constant | :heavy_multiplication_x: | :heavy_multiplication_x:

![constant pointer][const_pointer]

# Dynamic memory management
* malloc: allocate memory from heap
* free: release memory to the heap
* realloc: realloc memory to bigger or smaller amount previously allocated
* calloc: allocate memory and zero out content
* memory leak: not free, losing the address
* assign NULL to a freed pointer
* double free
* dangling pointer
* Mudflap libary: support detection of memory leak
* Garbage collection
* Boehm-Weiser collector
* Resource Acquisition Is Initialization (RAII): RAII_VARIABLE macro

# Pointers and Functions
* Program stack is an area of memory that supports the execution of functions and is normally shared with the heap.
 * stack frames, or activation records, or activation frames: hold parameters and local variables of a function
 * return address: the address in the program where the function is to return upon completion
 * storage for local data: memory allocated for local variables
 * storage for parameters: memory allocated for the function's parameters
 * stack and base pointers: pointers used by the runtime system to manage stack
* function pointer: `void (*foo)()` or `double* (*f3)(int, int)`
 * using a function pointer
```
int (*fptr1)(int);
int square(int num) {
    return num*num;
}
```
```
int n = 5;
fptr1 = square;
printf("%d squared is %d\n", n, fptr(n));
```
 * passing a function pointer
```
int add(int num1, int num2) {
    return num1+num2;
}
int subtract(int num1, int num2) {
    return num1-num2;
}
typedef int (*fptrOperation)(int, int);
int compute(fptrOperation op, int num1, int num2) {
    return op(num1, num2);
}
printf("%d\n", compute(add, 5, 6));
printf("%d\n", compute(subtract, 5, 6));
```
 * return a function pointer
```
fptrOperation select(char opcode) {
    switch(opcode) {
        case '+': return add;
        case '-': return subtract;
    }
}
```
 * array function pointer: `fptrOperatin operations[128] = {add, subtract};`
 * compare function pointer: functions pointer can be compared using equality (==) and inequality (!=) operators
 * casting function pointer: can be cast but should use with care since run time system doesn't verify parameters used by a function pointer a correct or not

# Pointers and Arrays
* Array is a contiguous collection of homogeneous elements that can be accessed using an index
* Two dimension array are typically use the terms rows and columns
* One dimension array: `int vector[5]`
 * Array index start at 0, and end with one less than the declared size
* Two dimension array use row and column to identify array element: `int matrix[2][3] = {{1,2,3},{4,5,6}}`
![two dimension array][two_dimension_array]
* pointer and array: we can assign an array to pointer
```
int vector[5] = {1,2,3,4,5};
int *pv = vector; // or int *pv = &vector[0];
```
 * Bracket notation will take the address contained in pointer and add the value contained in the index i using pointer arithmetic. pv[i] is evaluated as \*(pv + i)
 * \*(pv+i) is equavalent to \*(vector+i)
* difference between pointer and array
```
pv = pv + 1;
vector = vector + 1; // error
pv = vector + 1; // ok
```


[const_pointer]: https://github.com/hieuletrung/personal/raw/master/study/const_pointer.png "Constant pointer"
[two_dimension_array]: https://github.com/hieuletrung/personal/raw/master/study/two_dimension_array.png "Two dimension array"