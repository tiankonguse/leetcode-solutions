
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

tuple<int, int, int, int> ToP(const vector<int>& v) {
  int n = v.size();
  if (n == 0) {
    return {INT_MIN, INT_MIN, INT_MIN, INT_MIN};
  } else if (n == 1) {
    return {v[0], INT_MIN, INT_MIN, INT_MIN};
  } else if (n == 2) {
    return {v[0], v[1], INT_MIN, INT_MIN};
  } else if (n == 3) {
    return {v[0], v[1], v[2], INT_MIN};
  } else {
    return {v[0], v[1], v[2], v[3]};
  }
}

vector<int> buf;
vector<int>& ToV(const tuple<int, int, int, int>& t) {
  auto [t0, t1, t2, t3] = t;
  buf.clear();
  buf.push_back(t0);
  buf.push_back(t1);
  buf.push_back(t2);
  buf.push_back(t3);
  while (!buf.empty() && buf.back() == INT_MIN) {
    buf.pop_back();
  }
  return buf;
}

tuple<int, int, int, int> Merge(const tuple<int, int, int, int>& t, int p) {
  vector<int>& buf = ToV(t);
  buf.push_back(p);
  sort(buf.begin(), buf.end(), [](auto a, auto b) { return a > b; });
  return ToP(buf);
}

const pair<ll, tuple<int, int, int, int>> zero = {0, {INT_MIN, INT_MIN, INT_MIN, INT_MIN}};
class Solution {
 public:
  vector<int> maximumWeight(vector<vector<int>>& intervals) {
    int n = intervals.size();
    vector<tuple<int, int, ll, int>> nodes(n);  // <R, L, W, I>

    vector<int> nums;
    nums.reserve(n + 1);
    nums.push_back(0);  // 桩，避免 l-1 越界
    for (int i = 0; i < n; i++) {
      nodes[i] = {intervals[i][1], intervals[i][0], intervals[i][2], i};
      nums.push_back(intervals[i][1]);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    sort(nodes.begin(), nodes.end());

    int m = nums.size();
    vector<vector<pair<ll, tuple<int, int, int, int>>>> dp(4);
    for (int i = 0; i < 4; i++) {
      dp[i].resize(m, zero);
    }

    pair<ll, tuple<int, int, int, int>> ans = {0, {}};
    // f(k+1,r) = max(f(k+1,r), f(k+1,r-1))
    // f(k+1,r) = max(f(k+1,r), f(k, l-1) + w)
    for (int k = 0; k < 4; k++) {
      for (auto& node : nodes) {
        auto [r, l, w, p] = node;
        auto ri = lower_bound(nums.begin(), nums.end(), r) - nums.begin();
        if (k == 0) {
          pair<ll, tuple<int, int, int, int>> tmp = {w, {-p, INT_MIN, INT_MIN, INT_MIN}};
          dp[k][ri] = max(dp[k][ri], dp[k][ri - 1]);
          dp[k][ri] = max(dp[k][ri], tmp);
        } else {
          auto li = upper_bound(nums.begin(), nums.end(), l - 1) - nums.begin() - 1;
          auto [wl, vl] = dp[k - 1][li];
          pair<ll, tuple<int, int, int, int>> tmp = {wl + w, Merge(vl, -p)};

          dp[k][ri] = max(dp[k][ri], dp[k][ri - 1]);
          dp[k][ri] = max(dp[k][ri], tmp);
        }
        ans = max(ans, dp[k][ri]);
      }
    }
    // printf("ans=%lld\n", ans.first);
    vector<int>& buf = ToV(ans.second);
    for (auto& v : buf) {
      v = -v;
    }
    return buf;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<vector<int>> intervals, vector<int> ans) {  //
  TEST_SMP1(Solution, maximumWeight, ans, intervals);
}

int main() {
  Test({{1, 3, 2}, {4, 5, 2}, {1, 5, 5}, {6, 9, 3}, {6, 7, 1}, {8, 9, 1}}, {2, 3});
  Test({{5, 8, 1}, {6, 7, 7}, {4, 7, 3}, {9, 10, 6}, {7, 8, 2}, {11, 14, 3}, {3, 5, 5}}, {1, 3, 5, 6});
  Test({{1, 1, 1000000000}, {1, 1, 1000000000}, {1, 1, 1000000000}, {1, 1, 1000000000}}, {0});
  Test({{17, 17, 10}, {23, 23, 23}, {3, 8, 31}, {17, 21, 48}, {18, 24, 44}}, {1, 2, 3});
  return 0;
}

#endif