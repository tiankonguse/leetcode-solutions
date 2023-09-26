#include <iostream>
#include <vector>

class AA {
 public:
  virtual bool Foo(int input) = 0;
  virtual bool Foo(double input) = 0;
};

template <typename Input>
class A : public AA {
 public:
  virtual bool Foo(Input input) = 0;
};

template <>
class A<int> : public AA {
 public:
  virtual bool Foo(int input) = 0;
  virtual bool Foo(double input) { return this->Foo(int(input)); }
};

template <>
class A<double> : public AA {
 public:
  virtual bool Foo(double input) = 0;
  virtual bool Foo(int input) { return this->Foo(double(input)); }
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
