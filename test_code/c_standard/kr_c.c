/* K&R C */
void say_it(a, s)
 int a;
 char s[];
{
  printf("%s %d\n", s, a);
}
main()
{
  int a = 42;
  puts("Welcome to classic C");
  say_it(a, "the answer is");
}
