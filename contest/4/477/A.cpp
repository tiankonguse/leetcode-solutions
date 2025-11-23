
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  long long sumAndMultiply(int n) {
    // 非零数字 * 数字和
    ll sum = 0;
    ll num = 0;
    ll base = 1;
    while (n) {
      ll x = n % 10;
      sum += x;
      if (x) {
        num += x * base;
        base *= 10;
      }
      n /= 10;
    }
    return sum * num;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif