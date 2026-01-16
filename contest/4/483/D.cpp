
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
  vector<vector<int>> lists;
  vector<ll> medians;
  vector<ll> costs;
  vector<ll> lens;
  ll minVal, maxVal;
  int n;
  int M;
  void Init() {
    n = lists.size();
    M = 1 << n;
    medians.resize(M, INT64_MAX);
    costs.resize(M, INT64_MAX);
    minVal = INT64_MAX;
    maxVal = INT64_MIN;
    for (int i = 0; i < n; i++) {
      for (ll v : lists[i]) {
        minVal = min(minVal, v);
        maxVal = max(maxVal, v);
      }
    }
    lens.resize(M, 0);
    for (int mask = 0; mask < M; mask++) {
      for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
          lens[mask] += lists[i].size();
        }
      }
    }
  }
  ll Median(int mask) {  //
    ll& ret = medians[mask];
    if (ret != INT64_MAX) {
      return ret;
    }
    vector<int> ps;
    for (int i = 0; i < n; i++) {
      if (mask & (1 << i)) {
        ps.push_back(i);
      }
    }
    ll midCnt = (lens[mask] + 1) / 2;

    ll l = minVal, r = maxVal + 1;
    while (l < r) {
      ll len = r - l + 1;
      ll mid = l + (len - 1) / 2;
      ll cnt = 0;
      for (int i : ps) {
        cnt += upper_bound(lists[i].begin(), lists[i].end(), mid) - lists[i].begin();
      }
      if (cnt < midCnt) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return ret = l + 1;
  }
  ll Dfs(int mask) {
    ll& ret = costs[mask];
    if (ret != INT64_MAX) {
      return ret;
    }
    if ((mask & (mask - 1)) == 0) {
      return ret = 0;  // 1个，不需要合并
    }
    // 枚举所有子集
    for (int sub = (mask - 1) & mask; sub > (sub ^ mask); sub = (sub - 1) & mask) {
      int other = mask ^ sub;
      ret = min(ret, Dfs(sub) + Dfs(other) + lens[sub] + lens[other] + abs(Median(sub) - Median(other)));
    }
    return ret;
  }

 public:
  ll minMergeCost(vector<vector<int>>& lists_) {
    lists.swap(lists_);
    Init();
    return Dfs(M - 1);
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<vector<int>>& lists, const ll& ans) {
  TEST_SMP1(Solution, minMergeCost, ans, lists);  //
}

int main() {  //
  {
    // [[3,6,10],[-10,-5,-4,1]]
    vector<vector<int>> lists = {{3, 6, 10}, {-10, -5, -4, 1}};
    ll ans = 21;
    Test(lists, ans);
  }
  return 0;
}

#endif