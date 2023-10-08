#include <iostream>
#include <variant>
#include <vector>

template <class Input>
class A {
 public:
  virtual bool Foo(Input input) = 0;
};

class B : public A<int> {
 public:
  bool Foo(int input) override {
    std::cout << "int B::Foo(" << input << ")" << std::endl;
    return true;
  }
};

class C : public A<double> {
 public:
  bool Foo(double input) override {
    std::cout << "double C::Foo(" << input << ")" << std::endl;
    return true;
  }
};

int main() {
  
  std::vector<std::variant<B*, C*>> container;
  container.push_back(new B);
  container.push_back(new C);

  for (const auto& item : container) {
    double v = 3.2;
    std::visit([&v](auto&& p) { p->Foo(v); }, item);
  }

  return 0;
}