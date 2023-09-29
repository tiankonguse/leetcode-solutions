#include <iostream>
#include <vector>

class AA {
 public:
  virtual bool Foo(int input) {
    double a = input;
    return Foo(a);
  }
  virtual bool Foo(double input) {
    int a = input;
    return Foo(a);
  }
};

template <typename Input>
class A : public AA {
 public:
  virtual bool Foo(Input input) = 0;
};

class B : public A<int> {
 public:
  virtual bool Foo(int input) {
    printf("this is int, input=%d\n", input);
    return true;
  }
};

class C : public A<double> {
 public:
  virtual bool Foo(double input) {
    printf("this is double, input=%.2lf\n", input);
    return true;
  }
};

int main() {
  std::vector<AA*> vec;
  vec.push_back(new B);
  vec.push_back(new C);
  for (auto p : vec) {
    p->Foo(2);
  }

  return 0;
}
