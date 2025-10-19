
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
  int longestSubsequence(vector<int>& nums) {
    int n = nums.size();
    ll sum = 0;
    ll num = 0;
    for (ll v : nums) {
      sum ^= v;
      if (v != 0) {
        num++;
      }
    }
    if (sum != 0) {
      return n;
    }
    if (num > 0) {
      return n - 1;
    }
    return 0;
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