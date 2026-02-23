
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
  bool isDigitorialPermutation(int n) {
    vector<ll> factorials(10, 1);
    for (int i = 1; i < 10; ++i) {
      factorials[i] = factorials[i - 1] * i;
    }
    string digits = to_string(n);
    sort(digits.begin(), digits.end());
    ll sum = 0;
    for (auto digit : digits) {
      sum += factorials[digit - '0'];
    }
    string sumStr = to_string(sum);
    sort(sumStr.begin(), sumStr.end());
    return sumStr == digits;
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