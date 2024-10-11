#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

using namespace std;

struct IValue {
  IValue() : t_(0), e_(0) { memset(d_, 0, sizeof(d_)); }
  IValue(const IValue &v) : t_(0) {
    memset(d_, 0, sizeof(d_));
    *this = v;
  }

  uint8_t t_ : 8;   // 数据类型
  int32_t e_ : 24;  // 错误码
  char d_[8];       // 数据
};

int main() {
  IValue a;
  a.t_ = 1;
  a.e_ = 2;
  for (int i = 0; i < 8; i++) {
    a.d_[i] = '0' + i;
  }

  return 0;
}