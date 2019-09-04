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
* constant pointer modification
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

// Using
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

// Using
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
* passing one-dimension array: when one-dimension array is passed into function, array's address is passed by value.
 * using array notation
```
void displayArray(int arr[], int size) {
    for (int i=0; i<size; ++i) {
        printf("%d\n", arr[i]); // or printf("%d\n", *(arr+i));
    }
}

// Using
int vector[5] = {1,2,3,4,5};
displayArray(vector, 5);
```
 * using pointer notation
```
void displayArray(int *arr, int size) {
    for (int i=0; i<size; ++i) {
        printf("%d\n", arr[i]);  // or printf("%d\n", *(arr+i));
    }
}
```
* using one-dimension array of pointer
```
int *arr[5];
for (int i=0; i<5;++i) {
    arr[i] = (int *)malloc(sizeof(int));    // or *(arr+i) = (int *)malloc(sizeof(int));
    *arr[i] = i;                            // or **(arr+i) = i;
}
```
* pointers and multi-dimensional arrays: `int matrix[2][5] = {{1,2,3,4,5},{6,7,8,9,10}};`
 * we can declare a pointer for use with this array: `int (*pmatrix)[5] = matrix;`
 * access element using pointer notation
```
printf("%p\n", matrix);         // pointer to 1
printf("%p\n", matrix + 1);     // pointer to 6
```
 * `arr[i][j]`: address of arr + (i * size of row) + (j * size of element)
* passing a multidimension array
```
void displayArray(int arr[][5], int rows);
// or
void displayArray(int (*arr)[5], int rows);
```
 * we can pass a single pointer and number of rows and columns as following
 ```
 void display2DArrayUnknownSize(int *arr, int rows, int cols) {
    for (int i=0; i<rows; ++i) {
        for (int j=0; j<cols; ++j) {
            printf("%d ", *(arr + (i*cols) + j));
        }
        printf("\n");
    }
 }
 ```
* dynamically allocating a two dimensional array
 * whether the array elements need to be contiguous
 * whether the array is jagged
 * memory contiguous array: `int matrix[2][5] = {{1,2,3,4,5},{6,7,8,9,10}};`
 * allocate potentially noncontiguous memory, since two separated malloc are used, there is no guarantee to be contiguous memory block
```
int rows = 2;
int columns = 5;
int **matrix = (int **)malloc(rows * (sizeof(int *)));
for (int i=0; i<rows; ++i) {
    matrix[i] = (int *)malloc(columns * (sizeof(int)));
}
```
![noncontiguous allocation][noncontiguous_allocation]
 * allocate contiguous memory
```
int rows = 2;
int columns = 5;
int **matrix = (int **)malloc(rows * sizeof(int *));
matrix[0] = (int *)malloc(rows * columns * (sizeof(int)));
for (int i=0; i<rows; ++i) {
    matrix[i] = matrix[0] + (i * columns);
}

// or
int *matrix = (int *) malloc(rows * column * sizeof(int));
```
* Jagged arrays and pointers
 * Jagged array is a two dimensional array possessing a different number of columsn for each rows
```
int (*arr[])) = {
    (int[]) {0, 1, 2, 3},
    (int[]) {4, 5},
    (int[]) {6, 7, 8}
};
```

# Pointer and String
* String fundamentals
 * a string is a sequence of character terminated with the ASCII NUL character, or '\0'
 * two type of string in C
  * byte string: consist of a sequence of char data type
  * wide string: consist of a sequence of wchar_t data type, either 16 or 32 bits in width
 * length of string is number of characters in string, doesn't include NUL character. when memory is allocated for string, remember to allocate enough memory for all characters plus NUL character
 ```
 printf("%d\n", sizeof(char));  // 1
 printf("%d\n", sizeof('a'));   // 4
 ```
* string declaration: can be either as a literal, an array of characters, pointer to a character
 * string literal vs. character literal
* String literal pool
 * when literal are defined, they are frequently assigned to a literal pool. when literal is used more than once, there is normall ya single copy of the string in the literal pool. but it can be turned off be compiler.
 * gcc use -fwriteable-strings option to turn off string pooling.
 * string literal do not have scope
* string initialization
 * initialize an array of char
```
char header[] = "Media Player";
// or
char header[13];
strcpy(header, "Media Player");
```
 * initialize pointer to char
```
char *header = (char *)malloc(strlen("Media Player") + 1);
strcpy(header, "Media Player");
// or
char *header = "Media Player"; // not copy
```
 * initialize from standard input
 ```
 char *command;
 printf("Enter a command: ");
 scanf("%s", command);
 ```
 * string placement in memory
```
char *globalHeader = "Chapter";
char globalArrayHeader[] = "Chapter";

void displayHeader() {
    static char *staticHeader = "Chapter";
    char *localHeader = "Chapter";
    static char staticArrayHeader[] = "Chapter";
    char localArrayHeader[] = "Chapter";
    char *heapHeader = (char *)malloc(strlen("Chapter") + 1);
    strcpy(heapHeader, "Chapter");
}
```
![string allocation memory][string_allocation_memory]

* Standard string operation


[const_pointer]: https://github.com/hieuletrung/personal/raw/master/study/const_pointer.png "Constant pointer"
[two_dimension_array]: https://github.com/hieuletrung/personal/raw/master/study/two_dimension_array.png "Two dimension array"
[noncontiguous_allocation]: https://github.com/hieuletrung/personal/raw/master/study/noncontiguous_allocation.png "Noncontiguous memory allocation"
[string_allocation_memory]: https://github.com/hieuletrung/personal/raw/master/study/string_allocation_memory.png "String allocation memory"