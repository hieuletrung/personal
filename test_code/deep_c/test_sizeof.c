// gcc test_sizeof.c -o test_sizeof -Wall -g -Os

#include <stdio.h>
#include <stdlib.h>

int main() {
	int * q = malloc(sizeof(int));
	size_t p = sizeof * q;
	size_t apple = sizeof (int) * p;
	//size_t apple = sizeof (int) * q; // error: invalid operands to binary * (have ‘long unsigned int’ and ‘int *’)
									   // it treats as multiply

	printf("p size: %lu\n", p);
	printf("Apple size: %lu\n", apple);

	free(q);
	return 0;
}