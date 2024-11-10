
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
  pair<int, int> Parse(const string& num) {
    auto p = num.find('+');
    int a = std::stoi(num.substr(0, p));
    int b = std::stoi(num.substr(p + 1));
    return {a, b};
  }

 public:
  string complexNumberMultiply(const string& num1, const string& num2) {
    auto [a0, b0] = Parse(num1);
    auto [a1, b1] = Parse(num2);
    int a2 = a0 * a1 - b0 * b1;
    int b2 = a0 * b1 + a1 * b0;
    MyPrintf("[%d, %d] * [%d,%d] = [%d,%d]\n", a0, b0, a1, b1, a2, b2);
    return to_string(a2) + "+" + to_string(b2) + "i";
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(string num1, string num2, const string& ans) {
  TEST_SMP2(Solution, complexNumberMultiply, ans, num1, num2);
}

int main() {
  Test("1+1i", "1+1i", "0+2i");
  Test("1+-1i", "1+-1i", "0+-2i");
  Test("1+1i", "1+-1i", "2+0i");
  return 0;
}

#endif