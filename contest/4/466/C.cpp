
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
  inline int Abs(int x) { return x < 0 ? -x : x; }

 public:
  long long bowlSubarrays(vector<int>& nums) {
    int n = nums.size();
    vector<int> sta;  // (value, index) 单调递减
    sta.reserve(n);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
      const int v = nums[i];
      while (!sta.empty() && Abs(sta.back()) < v) {
        sta.pop_back();
        if (!sta.empty()) {
          ans++; // [sta.back(), v] 区间可以组成一个答案
        }
      }
      sta.push_back(-v);
    }
    return ans;
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