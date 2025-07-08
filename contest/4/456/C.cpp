
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
  vector<int> preXOR;
  vector<vector<int>> dp;
  int Dfs(int n, int k) {
    int& ret = dp[n][k];
    if (ret != -1) return ret;
    if (n == 0) return ret = 0;
    if (k == 1) return ret = preXOR[n];
    ret = INT_MAX;
    for (int i = n; i >= k; i--) {
      ret = min(ret, max(preXOR[n] ^ preXOR[i - 1], Dfs(i - 1, k - 1)));
    }
    return ret;
  }

 public:
  int minXor(vector<int>& nums, int k) {
    int n = nums.size();
    preXOR.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      preXOR[i] = preXOR[i - 1] ^ nums[i - 1];
    }
    dp.resize(n + 1, vector(k + 1, -1));
    return Dfs(n, k);
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