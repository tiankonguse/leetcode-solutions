
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
  int maxSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    if (nums.back() <= 0) {
      return nums.back();
    }

    int n = nums.size();
    int pre = INT_MAX;
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
      int v = nums[i];
      if (v == pre) continue;
      pre = v;
      if (v <= 0) break;
      ans += v;
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

int main() {  //
  return 0;
}

#endif