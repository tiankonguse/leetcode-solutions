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
  vector<ll> sumVal;

  void Init(int n) {
    n++;
    maxNM = n;
    sumVal.clear();
    sumVal.resize(maxNM << 2, 0);
  }

  void PushUp(int rt) { sumVal[rt] = sumVal[rt << 1] & sumVal[rt << 1 | 1]; }
  void Build(vector<int>& nums, int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      if (r <= nums.size()) {
        sumVal[rt] = nums[l - 1];
      } else {
        sumVal[rt] = INT_MAX;
      }
      return;
    }
    int m = (l + r) >> 1;
    Build(nums, lson);
    Build(nums, rson);
    PushUp(rt);
  }
  ll QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return sumVal[rt];
    }
    int m = (l + r) >> 1;
    ll ret = INT_MAX;
    if (L <= m) {
      ret = ret & QuerySum(L, R, lson);
    }
    if (m < R) {
      ret = ret & QuerySum(L, R, rson);
    }
    return ret;
  }
};

SegTree segTree;
class Solution {
 public:
  int minimumDifference(vector<int>& nums, ll k) {
    int n = nums.size();
    segTree.Init(n);
    segTree.Build(nums);

    ll ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
      int l = i;
      int r = n;
      // printf("i=%d \n", i);
      while (l < r) {
        int mid = (l + r) / 2;
        ll tmp = segTree.QuerySum(i, mid);
        // printf("l=%d r=%d tmp=%lld k=%lld\n", l,r,tmp, k);
        ans = min(ans, abs(k - tmp));
        if (tmp > k) {
          l = mid + 1;
        } else if (tmp < k) {
          r = mid;
        } else {
          return 0;
        }
      }
      ans = min(ans, abs(k - segTree.QuerySum(i, l)));
      if (l > i) {
        ans = min(ans, abs(k - segTree.QuerySum(i, l - 1)));
      }
      if (l < n) {
        ans = min(ans, abs(k - segTree.QuerySum(i, l + 1)));
      }
    }
    return ans;
  }
};
