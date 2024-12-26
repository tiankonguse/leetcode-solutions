// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
struct SegTree {
  vector<ll> sign;
  vector<pair<ll, int>> minVal;
  vector<pair<ll, int>> maxVal;
  vector<ll> sumVal;
  vector<ll> nums;
  vector<ll> str;

  void Init(int n) {
    n++;
    maxNM = n;
    sign.resize(maxNM << 2, 0);
    minVal.resize(maxNM << 2);
    maxVal.resize(maxNM << 2);
    sumVal.resize(maxNM << 2, 0);
    nums.resize(maxNM << 2, 0);
    str.clear();
    str.resize(maxNM + 1, 0);
  }

  void PushUp(int rt) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
  }
  void PushDown(int rt) {
    if (sign[rt]) {
      sign[rt << 1] += sign[rt];
      sign[rt << 1 | 1] += sign[rt];

      minVal[rt << 1].first += sign[rt];
      minVal[rt << 1 | 1].first += sign[rt];

      maxVal[rt << 1].first += sign[rt];
      maxVal[rt << 1 | 1].first += sign[rt];

      sumVal[rt << 1] += sign[rt] * nums[rt << 1];
      sumVal[rt << 1 | 1] += sign[rt] * nums[rt << 1 | 1];

      sign[rt] = 0;
    }
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    nums[rt] = r - l + 1;
    if (l == r) {
      sumVal[rt] = str[l];
      minVal[rt] = maxVal[rt] = {str[l], l};
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt);
  }
  void Update(int L, int R, int add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      sign[rt] += add;
      minVal[rt].first += add;
      maxVal[rt].first += add;
      sumVal[rt] += add * nums[rt];
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
    PushUp(rt);
  }
  pair<ll, int> QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxVal[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    pair<ll, int> ret = {-1, 0};
    if (L <= m) {
      ret = max(ret, QueryMax(L, R, lson));
    }
    if (m < R) {
      ret = max(ret, QueryMax(L, R, rson));
    }
    return ret;
  }
  pair<ll, int> QueryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    pair<ll, int> ret = {__LONG_LONG_MAX__, 0};
    if (L <= m) {
      ret = min(ret, QueryMin(L, R, lson));
    }
    if (m < R) {
      ret = min(ret, QueryMin(L, R, rson));
    }
    return ret;
  }
  ll QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return sumVal[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    ll ret = 0;
    if (L <= m) {
      ret += QuerySum(L, R, lson);
    }
    if (m < R) {
      ret += QuerySum(L, R, rson);
    }
    return ret;
  }
};

SegTree segTree;
class Solution {
 public:
  vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2,
                                vector<vector<int>>& queries) {
    vector<tuple<int, int, int>> qs;
    qs.reserve(queries.size());
    for (int i = 0; i < queries.size(); i++) {
      qs.push_back({queries[i][0], queries[i][1], i});
    }
    sort(qs.begin(), qs.end());

    unordered_map<ll, ll> maxYX;
    // 对于同一个 y，取最大的 x 的下标
    for (int i = 0; i < nums1.size(); i++) {
      ll x = nums1[i];
      ll y = nums2[i];

      if (maxYX.count(y) == 0) {
        maxYX[y] = i + 1;
      } else {
        if (x > nums1[maxYX[y] - 1]) {
          maxYX[y] = i + 1;
        }
      }
    }

    vector<pair<ll, ll>> nums;
    nums.reserve(nums1.size());
    for (int i = 0; i < nums1.size(); i++) {
      ll x = nums1[i];
      ll y = nums2[i];
      if (maxYX[y] == i + 1) {
        nums.push_back({x, y});
      }
    }
    sort(nums.begin(), nums.end());

    if (1) {  // 离散化
      for (auto [x, y, i] : qs) {
        maxYX[y] = 0;
      }
      int p = 1;
      for (auto& [y, i] : maxYX) {
        i = p;
        p++;
      }
    }

    segTree.Init(maxYX.size() + 5);
    segTree.Build();
    for (auto [x, y] : nums) {
      int l = maxYX[y];
      segTree.Update(l, l, x + y);
    }

    vector<int> ans(queries.size());

    int p = 0;
    for (auto [x, y, ansIndex] : qs) {
      while (p < nums.size() && nums[p].first < x) {
        auto [X, Y] = nums[p];
        int l = maxYX[Y];
        segTree.Update(l, l, -X - Y);
        p++;
      }

      int l = maxYX[y];
      ans[ansIndex] = segTree.QueryMax(l, maxYX.size()).first;
      if (ans[ansIndex] == 0) {
        ans[ansIndex] = -1;
      }
    }

    return ans;
  }
};