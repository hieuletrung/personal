// C++ (C++98)
#include <cstdio>
struct X {
  int a;
  const char * s;
  
  explicit X(const char * s, int a = 42) : a(a), s(s) {}

  void say_it() const {
    std::printf("%s %d\n", s, a);
  }
};

int main()
{
  X("the answer is").say_it();
}
