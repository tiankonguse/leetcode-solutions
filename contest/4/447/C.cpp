
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
  int CalBit(int x) {
    int ret = 0;
    while (x) {
      ret++;
      x /= 10;
    }
    return ret;
  }

 public:
  vector<int> concatenatedDivisibility(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    vector<int> ans;
    int n = nums.size();
    int N = 1 << n;
    vector<vector<int>> dp(k, vector<int>(N, -1));
    vector<vector<int>> path(k, vector<int>(N, -1));
    vector<int> bits(n, 0);
    for (int i = 0; i < n; i++) {
      bits[i] = CalBit(nums[i]);
    }
    vector<int> pow10 = {1, 10, 100, 1000, 10000, 100000, 1000000};
    auto dfs = [&](auto& dfs, const int pre, const int mask) {
      int& ret = dp[pre][mask];
      if (ret != -1) {
        return ret;
      }
      if (mask == 0) {
        return ret = pre == 0;
      }

      for (int i = 0; i < nums.size(); ++i) {
        if (mask & (1 << i) && dfs(dfs, (pre * pow10[bits[i]] + nums[i]) % k, mask ^ (1 << i))) {
          path[pre][mask] = i;
          return ret = 1;
        }
      }
      return ret = 0;
    };

    if (dfs(dfs, 0, N - 1) == 0) {
      return ans;
    }

    // 得到 path
    int pre = 0;
    int mask = N - 1;
    ans.reserve(n);
    while (mask) {
      int i = path[pre][mask];
      ans.push_back(nums[i]);
      pre = (pre * pow10[bits[i]] + nums[i]) % k;
      mask ^= (1 << i);
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