#include <iostream>
#include <typeinfo>
#include <vector>

class AA {
  std::size_t hash_code_;

 public:
  template <typename Input>
  void SetTypeid() {
    this->hash_code_ = typeid(Input).hash_code();
  }

  template <typename Input>
  bool Forward(Input input) {
    if (typeid(int).hash_code() == this->hash_code_) {
      return this->FooInt(input);
    }
    if (typeid(double).hash_code() == this->hash_code_) {
      return this->FooDouble(tmp);
    }
    abort();
    return false;
  }
  bool FooInt(int input) { return Foo(input); }
  bool FooDouble(double input) { return Foo(input); }

  virtual bool Foo(int input) { return Forward(input); }
  virtual bool Foo(double input) { return Forward(input); }
};

template <typename Input>
class A : public AA {
 public:
  A() { this->SetTypeid<Input>(); }
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
