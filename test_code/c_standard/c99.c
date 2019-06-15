// C99
struct X
{
  int a;
  char * s;
};

int main(void)
{
  puts("Welcome to C99");
  struct X x = { .s = "the answer is", .a = 42 };
  printf("%s %d\n", x.s, x.a);
}
