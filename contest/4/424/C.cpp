
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
  int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
    ll sum = 0;
    for (auto v : nums) {
      sum += v;
    }
    if (sum == 0) {
      return 0;
    }

    vector<ll> ops;
    auto Check = [&nums, &queries, &ops](int mid) {
      int n = nums.size();
      ops.clear();
      ops.resize(n + 1, 0);
      for (int i = 0; i <= mid; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        ll val = queries[i][2];
        ops[l] -= val;
        ops[r + 1] += val;
      }
      ll pre = 0;
      for (int i = 0; i < n; i++) {
        pre += ops[i];
        if (nums[i] + pre > 0) return false;
      }
      return true;
    };

    int q = queries.size();
    int l = 0;
    int r = q;
    while (l < r) {  // [l, r)
      int mid = (l + r) / 2;
      if (Check(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    if (r < q) {
      return r + 1;
    } else {
      return -1;
    }
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& nums, const vector<vector<int>>& queries,
          const int& ans) {
  TEST_SMP2(Solution, minZeroArray, ans, nums, queries);
}

int main() {
  vector<int> nums = {2, 0, 2};
  vector<vector<int>> queries = {{0, 2, 1}, {0, 2, 1}, {1, 1, 3}};
  Test(nums, queries, 2);

  nums = {4, 3, 2, 1};
  queries = {{1, 3, 2}, {0, 2, 1}};
  Test(nums, queries, -1);

  nums = {0, 0, 0};
  queries = {{1, 3, 2}, {0, 2, 1}};
  Test(nums, queries, 0);
  return 0;
}

#endif