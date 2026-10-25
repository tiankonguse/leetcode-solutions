
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
/*
思路：模拟，计算两个数字二进制1的个数，然后按题意比较，返回对应的答案

*/
class Solution {
 public:
  int calculateScore(int a, int b) {
    int s1 = __builtin_popcount(a);
    int s2 = __builtin_popcount(b);
    if (s1 >= s2) {
      return s1 * s2;
    } else {
      return s2 / s1;
    }
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