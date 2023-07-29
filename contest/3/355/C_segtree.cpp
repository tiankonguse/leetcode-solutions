// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

// 1.bulid(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM = 0;

struct SegTree {
  vector<ll> sign;
  vector<pair<ll, int>> minVal;
  vector<pair<ll, int>> maxVal;
  vector<ll> sumVal;
  vector<ll> nums;

  void Init(int n) {
    if (maxNM == 0) {
      maxNM = 1e5 + 2;
      sign.resize(maxn << 2, 0);
      minVal.resize(maxn << 2);
      maxVal.resize(maxn << 2);
      sumVal.resize(maxn << 2, 0);
      nums.resize(maxn << 2, 0);
    }
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
  void Bulid(vector<int>& str, int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    nums[rt] = r - l + 1;
    if (l == r) {
      ll v = 0;
      if (l - 1 < str.size()) {
        v = str[l - 1];
      }
      sumVal[rt] = v;
      minVal[rt] = maxVal[rt] = {v, l};
      return;
    }
    int m = (l + r) >> 1;
    Bulid(str, lson);
    Bulid(str, rson);
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
  int n;

  int Find(ll v) {  // 找到大于等于  v 的第一个位置
    int l = 1, r = n + 1;
    while (l < r) {
      int mid = (l + r) / 2;
      ll V = segTree.QuerySum(mid, mid);
      if (V > v) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return r - 1;
  }

 public:
  int maxIncreasingGroups(vector<int>& nums) {
    sort(nums.begin(), nums.end(), [](auto& a, auto& b) { return a > b; });
    n = nums.size();
    segTree.Init(n + 2);
    segTree.Bulid(nums);
    // for (int i = 1; i <= n; i++) {
    //   segTree.Update(i, i, nums[i - 1]);
    // }
    // printf("n+1 = %d\n", treeArray.Query(n + 1, n + 1));

    int ans = 0;

    while (segTree.QuerySum(ans + 1, ans + 1) > 0) {
      ans++;

      ll v = segTree.QuerySum(ans, ans);
      // printf("ans=%d v=%lld\n", ans, v);

      int L = 1, R = Find(v);
      int r = Find(v - 1);
      if (R > 0) {
        // printf("more L=%d R=%d\n", L, R);
        segTree.Update(L, R, -1);
      }

      int left = ans - R;
      if (left > 0) {
        int l = r - left + 1;
        // printf("less l=%d r=%d\n", l, r);
        segTree.Update(l, r, -1);
      }
    }

    return ans;
  }
};