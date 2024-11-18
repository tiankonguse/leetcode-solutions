
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
  bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
    int n = nums.size();
    vector<ll> ops(n + 1, 0);
    for (auto& q : queries) {
      int l = q[0];
      int r = q[1];
      ops[l]--;
      ops[r + 1]++;
    }
    ll pre = 0;
    for (int i = 0; i < n; i++) {
      pre += ops[i];
      if (nums[i] + pre > 0) return false;
    }
    return true;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& nums, const vector<vector<int>>& queries,
          const bool& ans) {
  TEST_SMP2(Solution, isZeroArray, ans, nums, queries);
}

int main() {
  vector<int> nums = {1, 0, 1};
  vector<vector<int>> queries = {{0, 2}};
  Test(nums, queries, true);

  nums = {4, 3, 2, 1};
  queries = {{1, 3}, {0, 2}};
  Test(nums, queries, false);
  return 0;
}

#endif