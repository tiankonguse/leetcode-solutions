// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

// 1.bulid(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

struct SegTree {
  vector<ll> sign;
  vector<pair<ll, int>> maxVal;
  vector<ll> nums;
  vector<ll> str;

  void Init(vector<int>& input) {
    maxNM = input.size() + 1;
    sign.resize(maxNM << 2, 0);
    maxVal.resize(maxNM << 2);
    nums.resize(maxNM << 2, 0);
    str.clear();
    str.resize(maxNM + 1, 0);
    for (int i = 1; i <= input.size(); i++) {
      str[i] = input[i - 1];
    }
  }

  void PushUp(int rt) {
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
  }
  void PushDown(int rt) {
    if (sign[rt]) {
      sign[rt << 1] += sign[rt];
      sign[rt << 1 | 1] += sign[rt];

      maxVal[rt << 1].first += sign[rt];
      maxVal[rt << 1 | 1].first += sign[rt];

      sign[rt] = 0;
    }
  }
  void Bulid(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    nums[rt] = r - l + 1;
    if (l == r) {
      maxVal[rt] = {str[l], l};
      return;
    }
    int m = (l + r) >> 1;
    Bulid(lson);
    Bulid(rson);
    PushUp(rt);
  }
  void Update(int L, int R, int add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      sign[rt] += add;
      maxVal[rt].first += add;
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
};

SegTree segTree;
class Solution {
 public:
  vector<int> leftmostBuildingQueries(vector<int>& heights,
                                      vector<vector<int>>& queries) {
    segTree.Init(heights);
    segTree.Bulid();

    // 不存在答案时，返回 0
    auto Solver = [&heights](int u, int v) -> int {
      if (u > v) swap(u, v);
      if (u == v) return u;  // 特殊情况 1

      const int n = heights.size();
      const int uv = heights[u - 1];
      const int vv = heights[v - 1];
      if (vv > uv) {  // 特殊情况 2
        return v;
      }

      //   printf("q: u=%d uv=%d v=%d vv=%d\n", u, uv, v, vv);
      int l = v, r = n + 1;  //[l, r]
      while (l < r) {
        int mid = (l + r) / 2;
        int maxVal = segTree.QueryMax(l, mid).first;
        if (maxVal > uv && maxVal > vv) {  // 找到答案
          r = mid;
        } else {
          l = mid + 1;
        }
      }

      if (r == n + 1) {
        return 0;
      }
      return r;
    };

    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      ans.push_back(Solver(q[0] + 1, q[1] + 1) - 1);
    }
    return ans;
  }
};