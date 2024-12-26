// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM = maxn;

typedef long long ll;
struct SegTree {
  // vector<ll> sign;
  vector<ll> minVal;
  vector<ll> maxVal;
  // vector<ll> sumVal;
  // vector<ll> nums;
  // vector<ll> str;

  void Init(int n, vector<int>& strEx) {
    // n++;
    maxNM = n;
    // sign.resize(maxNM << 2, 0);
    if (minVal.size() == 0) {
      minVal.resize(maxn << 2);
      maxVal.resize(maxn << 2);
      // str.resize(maxNM + 1, 0);
    }
    // sumVal.resize(maxNM << 2, 0);
    // nums.resize(maxNM << 2, 0);
    // str.clear();
    // fill(str.begin(), str.end(), 0);
    // for (int i = 1; i <= strEx.size(); i++) {
    //   str[i] = strEx[i - 1];
    // }
  }

  void PushUp(int rt) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
    // sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
  }
  // void PushDown(int rt) {
  //   if (sign[rt]) {
  //     sign[rt << 1] += sign[rt];
  //     sign[rt << 1 | 1] += sign[rt];

  //     minVal[rt << 1].first += sign[rt];
  //     minVal[rt << 1 | 1].first += sign[rt];

  //     maxVal[rt << 1].first += sign[rt];
  //     maxVal[rt << 1 | 1].first += sign[rt];

  //     // sumVal[rt << 1] += sign[rt] * nums[rt << 1];
  //     // sumVal[rt << 1 | 1] += sign[rt] * nums[rt << 1 | 1];

  //     sign[rt] = 0;
  //   }
  // }
  void Build(vector<int>& strEx, int l = 1, int r = maxNM, int rt = 1) {
    // sign[rt] = 0;
    // nums[rt] = r - l + 1;
    if (l == r) {
      // sumVal[rt] = str[l];
      minVal[rt] = maxVal[rt] = strEx[l-1];
      return;
    }
    int m = (l + r) >> 1;
    Build(strEx, lson);
    Build(strEx, rson);
    PushUp(rt);
  }
  // void Update(int L, int R, int add, int l = 1, int r = maxNM, int rt = 1) {
  //   if (L <= l && r <= R) {
  //     sign[rt] += add;
  //     minVal[rt].first += add;
  //     maxVal[rt].first += add;
  //     // sumVal[rt] += add * nums[rt];
  //     return;
  //   }
  //   PushDown(rt);
  //   int m = (l + r) >> 1;
  //   if (L <= m) Update(L, R, add, lson);
  //   if (R > m) Update(L, R, add, rson);
  //   PushUp(rt);
  // }
  ll QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxVal[rt];
    }
    // PushDown(rt);
    int m = (l + r) >> 1;
    ll ret = -1;
    if (L <= m) {
      ret = max(ret, QueryMax(L, R, lson));
    }
    if (m < R) {
      ret = max(ret, QueryMax(L, R, rson));
    }
    return ret;
  }
  ll QueryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    // PushDown(rt);
    int m = (l + r) >> 1;
    ll ret = __LONG_LONG_MAX__;
    if (L <= m) {
      ret = min(ret, QueryMin(L, R, lson));
    }
    if (m < R) {
      ret = min(ret, QueryMin(L, R, rson));
    }
    return ret;
  }
};

SegTree segTree;
class Solution {
 public:
  ll continuousSubarrays(vector<int>& nums) {
    int n = nums.size();
    segTree.Init(n, nums);
    segTree.Build(nums);
    // for (int i = 1; i <= n; i++) {
    //   segTree.Update(i, i, nums[i - 1]);
    // }

    ll ans = 0;
    int preMaxPos = 1;
    for (int i = 1; i <= n; i++) {
      int l = max(i, preMaxPos), r = n + 1;  // [l, r)
      while (l < r) {
        int mid = (l + r) / 2;
        ll minVal = segTree.QueryMin(i, mid);
        ll maxVal = segTree.QueryMax(i, mid);
        // printf("i=%d mid=%d minVal=%d maxVal=%d\n", i, mid, minVal, maxVal);
        if (maxVal - minVal <= 2) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      preMaxPos = r-1;
      ans += r - i;
    }
    return ans;
  }
};