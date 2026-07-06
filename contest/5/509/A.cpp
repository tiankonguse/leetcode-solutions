
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
  int DigitRange(int a) {
    int maxVal = a % 10;
    int minVal = a % 10;
    while (a > 0) {
      int digit = a % 10;
      maxVal = max(maxVal, digit);
      minVal = min(minVal, digit);
      a /= 10;
    }
    return maxVal - minVal;
  }

 public:
  int maxDigitRange(vector<int>& nums) {
    int sum = 0;
    int maxValDigitRange = 0;
    for (const auto a : nums) {
      const int digitRange = DigitRange(a);
      if (digitRange > maxValDigitRange) {
        maxValDigitRange = digitRange;
        sum = a;
      } else if (digitRange == maxValDigitRange) {
        sum += a;
      }
    }
    return sum;
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