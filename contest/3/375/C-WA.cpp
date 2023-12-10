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

typedef long long ll;
struct SegTree {
  vector<ll> sign;
  vector<pair<ll, int>> minVal;
  vector<pair<ll, int>> maxVal;
  vector<ll> sumVal;
  vector<ll> nums;
  vector<ll> str;

  void Init(int n, vector<int>& input) {
    n++;
    maxNM = n;
    sign.resize(maxNM << 2, 0);
    minVal.resize(maxNM << 2);
    maxVal.resize(maxNM << 2);
    sumVal.resize(maxNM << 2, 0);
    nums.resize(maxNM << 2, 0);
    str.clear();
    str.resize(maxNM + 1, 0);
    for (int i = 0; i < input.size(); i++) {
      str[i + 1] = input[i];
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
  void Bulid(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    nums[rt] = r - l + 1;
    if (l == r) {
      sumVal[rt] = str[l];
      minVal[rt] = maxVal[rt] = {str[l], l};
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

int QueryMax(int l, int r) { return segTree.QueryMax(l + 1, r + 1).first; }

class Solution {
 public:
  ll countSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, vector<int>> stat;
    vector<int> h(n, -1);

    for (int i = 0; i < n; i++) {
      int v = nums[i];
      stat[v].push_back(i);
      h[i] = stat[v].size() - 1;
    }

    segTree.Init(n, nums);
    segTree.Bulid();

    // 向左，找到连续小于 v 的边界
    auto SearchLeft = [&nums](const int P) -> int {
      const int V = nums[P];
      int l = 0;
      int r = P;
      while (l < r) {  // [l, r)
        int mid = (l + r) / 2;
        if (QueryMax(mid, P - 1) < V) {
          r = mid;
        } else {
          l = mid + 1;
        }
      }
      return P - r + 1;
    };

    // 向右，找到不大于 v 的边界
    auto SearchRight = [&nums](const int P) -> int {
      const int V = nums[P];
      int l = P;
      int r = nums.size();
      while (l < r) {  //[l, r)
        int mid = (l + r) / 2;
        if (QueryMax(P, mid) <= V) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      return r - P;
    };

    ll ans = 0;
    for (int i = 0; i < n; i++) {  // 以 nums[i] 为子数组左边的第一个最大值
      int v = nums[i];
      int offset = h[i];
      if (offset + k > stat[v].size()) {
        continue;  // 不够 k 个
      }

      int l = i;
      int r = stat[v][offset + k - 1];
      if (QueryMax(l, r) > v) {
        continue;  // 连续 k 个 v 所在最小区间内，有更大的值
      }

      // 至少有一个答案
      ll leftNum = SearchLeft(l);
      ll rightNum = SearchRight(r);
      printf("i=%d v=%d leftNum=%lld, rightNum=%lld\n", i, v, leftNum,
             rightNum);
      ans += leftNum * rightNum;
    }
    return ans;
  }
};