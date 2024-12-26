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
  vector<ll> sumVal;
  // vector<ll> nums;
  // vector<pair<ll, ll>> LR;
  vector<ll> str;

  void Init(int n, vector<int>& nums_) {
    n += 5;
    maxNM = n;
    sumVal.resize(maxNM << 2, 0);
    // nums.resize(maxNM << 2, 0);
    // LR.resize(maxNM << 2);
    str.clear();
    str.resize(maxNM + 1, INT_MAX);
    for (int i = 0; i < nums_.size(); i++) {
      str[i + 2] = nums_[i];
    }
  }

  bool Check(int l, int r, int m) {  // [l,m] [m+1, r]
    if (l < m && str[m] > str[m - 1] && str[m] > str[m + 1]) return true;
    if (m + 1 < r && str[m + 1] > str[m + 2] && str[m + 1] > str[m])
      return true;
    return false;
  }

  void PushUp(int rt, int l, int r) {  //
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
    if (Check(l, r, (l + r) >> 1)) {
      sumVal[rt]++;
    }
  }

  void Build(int l = 1, int r = maxNM, int rt = 1) {
    // LR[rt] = {l, r};
    if (l == r) {
      sumVal[rt] = 0;
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, int R, int add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      sumVal[rt] = 0;
      str[l] = add;
      // sumVal[rt] += add * nums[rt];
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
    PushUp(rt, l, r);
  }
  ll QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return sumVal[rt];
    }
    int m = (l + r) >> 1;
    ll ret = 0;
    if (L <= m) {
      ret += QuerySum(L, R, lson);
    }
    if (m < R) {
      ret += QuerySum(L, R, rson);
    }
    if (L <= m && m < R && Check(max(l, L), min(r, R), m)) {
      ret++;
    }
    return ret;
  }
};

SegTree segTree;

class Solution {
 public:
  vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
    int n = nums.size();
    segTree.Init(n, nums);
    segTree.Build();

    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& v : queries) {
      int op = v[0];
      if (op == 1) {
        int l = v[1] + 2, r = v[2] + 2;
        ans.push_back(segTree.QuerySum(l, r));
      } else {
        int index = v[1] + 2;
        ll val = v[2];
        segTree.Update(index, index, val);
      }
    }
    return ans;
  }
};