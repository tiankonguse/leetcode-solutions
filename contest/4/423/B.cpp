
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  int maxIncreasingSubarrays(vector<int>& nums) {
    int n = nums.size();
    vector<int> flag(n + 1, 0);
    int l = 0, r = 0;
    int ans = 1;
    int preLen = 1;
    while (r < n) {
      l = r;
      while (r + 1 < n && nums[r] < nums[r + 1]) {
        r++;
      }
      for (int i = l; i <= r; i++) {
        flag[i] = r - i + 1;
      }

      int len = r - l + 1;
      ans = max(ans, len / 2);
      ans = max(ans, min(preLen, len));
      preLen = len;
      r++;
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& nums, const int& ans) {
  TEST_SMP1(Solution, maxIncreasingSubarrays, ans, nums);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif