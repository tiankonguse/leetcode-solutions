
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
ll dp[111][111][111];
class Solution {
  int K;
  vector<int> nums;
  ll Dfs(int n, int op1, int op2) {
    if (n < 0) return 0;
    ll& ret = dp[n][op1][op2];
    if (ret != -1) return ret;

    const ll oldVal = nums[n];
    const ll op1Val = (oldVal + 1) / 2;
    const ll op2Val = oldVal - K;

    ret = oldVal + Dfs(n - 1, op1, op2);
    if (op1 > 0) {
      ret = min(ret, op1Val + Dfs(n - 1, op1 - 1, op2));
    }
    if (op2 > 0 && op2Val >= 0) {
      ret = min(ret, op2Val + Dfs(n - 1, op1, op2 - 1));
    }

    if (op1 > 0 && op2 > 0 && op1Val >= K) {
      ll op12Val = op1Val - K;
      ret = min(ret, op12Val + Dfs(n - 1, op1 - 1, op2 - 1));
    }

    if (op1 > 0 && op2 > 0 && op2Val >= 0) {
      ll op21Val = (op2Val + 1) / 2;
      ret = min(ret, op21Val + Dfs(n - 1, op1 - 1, op2 - 1));
    }
    return ret;
  }

 public:
  int minArraySum(vector<int>& nums_, int k, int op1, int op2) {
    memset(dp, -1, sizeof(dp));
    this->K = k;
    this->nums.swap(nums_);
    int n = nums.size();
    return Dfs(n - 1, op1, op2);
  }
};
#ifdef USACO_LOCAL_JUDGE

void Test(vector<int> nums, int k, int op1, int op2, int ans) {
  TEST_SMP4(Solution, minArraySum, ans, nums, k, op1, op2);
}

int main() {
  Test({2, 8, 3, 19, 3}, 3, 1, 1, 23);
  Test({2, 4, 3}, 3, 2, 1, 3);
  return 0;
}

#endif