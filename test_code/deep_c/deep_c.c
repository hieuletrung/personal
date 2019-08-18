// gcc -Wall -o deep_c deep_c.c

#include <stdio.h>

void foo(void) {
  int a = 41;
  a = a++;
  printf("%d\n", a);
}

void access_array(void) {
  char a[20];
  a[3] = 'x';
  4[a] = 'y';
  printf("a[3] = %c\n", a[3]);
  printf("a[4] = %c\n", a[4]); 
}

int main(void) {
  foo();
}
