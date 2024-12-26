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
  vector<ll> nums;
  vector<ll> str;

  void Init(int n) {
    n++;
    maxNM = n;
    sign.resize(maxNM << 2, 0);
    sumVal.resize(maxNM << 2, 0);
    nums.resize(maxNM << 2, 0);
    str.clear();
    str.resize(maxNM + 1, 0);
  }

  void PushUp(int rt) { sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1]; }
  void PushDown(int rt) {
    if (sign[rt]) {
      sign[rt << 1] = sign[rt];
      sign[rt << 1 | 1] = sign[rt];

      sumVal[rt << 1] = nums[rt << 1];
      sumVal[rt << 1 | 1] = nums[rt << 1 | 1];

      sign[rt] = 0;
    }
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    nums[rt] = r - l + 1;
    if (l == r) {
      sumVal[rt] = str[l];
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt);
  }
  void Update(int L, int R, int add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      sign[rt] = 1;
      sumVal[rt] = nums[rt];
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
    PushUp(rt);
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
  int findMinimumTime(vector<vector<int>>& tasks_) {
    vector<tuple<int, int, int>> tasks;
    tasks.reserve(tasks_.size());
    for (auto& v : tasks_) {
      tasks.push_back({v[0], v[1], v[2]});
    }
    int n = tasks.size();

    sort(tasks.begin(), tasks.end(), [](auto& a, auto& b) {
      auto [ab, ae, ad] = a;
      auto [bb, be, bd] = b;
      if (ae == be) {
        return ad < bd;
      } else {
        return ae < be;
      }
    });

    segTree.Init(2010);
    segTree.Build();

    for (const auto [b, e, d] : tasks) {
      // printf("b=%d e=%d d=%d sum=%lld\n", b, e, d, segTree.QuerySum(b, e));
      if (segTree.QuerySum(b, e) >= d) {
        continue;
      }
      int l = b, r = e + 1;  // [l, e) // 至少染色一个
      while (l < r) {
        int mid = (l + r) / 2;
        // [l, mid) 不变， [mid, e] 全部染色
        int tmp = e - mid + 1;
        if (b < mid) {
          tmp += segTree.QuerySum(b, mid-1);
        }

        if (tmp > d) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      // printf("l=%d r=%d e=%d sum=%lld\n", l, r, e, segTree.QuerySum(b, e));
      segTree.Update(r, e, 1);
      // printf("l=%d r=%d sum=%lld\n", l, r, segTree.QuerySum(b, e));
    }
    return segTree.QuerySum(1, 2000);
  }
};