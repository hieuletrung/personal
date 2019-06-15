/* C89 */
void say_it(int a, char * s)
{
  printf("%s %d\n", s, a);
}

main()
{
  int a = 42;
  puts("Welcome to C89");
  say_it(a, "the answer is");
}
