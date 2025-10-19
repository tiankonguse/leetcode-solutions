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

/*
线段树：区间修改，区间查询

输入数组： vector<int> str; [0, n-1]

SegTree segTree;
segTree.Init(str); // 内部会对数组进行右移，转化为 [1,n]
segTree.Build();
segTree.Update(l, r, val); // 区间 [l,r] 都加上 val, 数据范围 [1,n]
segTree.QueryMax/QueryMin/QuerySum 区间查询, 数据范围 [1,n]
*/

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
struct SegTree {
  vector<ll> sign;               // 延迟标记
  vector<pair<ll, int>> minVal;  // 记录最值的位置
  vector<pair<ll, int>> maxVal;  // 记录最值的位置
  vector<ll> sumVal;             // 记录区间和
  vector<pair<ll, ll>> ranges;   // 节点对应的区间
  vector<ll> str;                // 原始数组的值，用于快速初始化

  void Init(int n, const ll default_val = 0) {
    maxNM = n + 1;
    sign.resize(maxNM << 2, 0);
    minVal.resize(maxNM << 2);
    maxVal.resize(maxNM << 2);
    sumVal.resize(maxNM << 2);
    ranges.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1, default_val);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
  }
  int Num(pair<ll, ll> p) { return p.second - p.first + 1; }
  void PushDown(int rt) {
    if (sign[rt]) {
      sign[rt << 1] += sign[rt];
      sign[rt << 1 | 1] += sign[rt];

      minVal[rt << 1].first += sign[rt];
      minVal[rt << 1 | 1].first += sign[rt];

      maxVal[rt << 1].first += sign[rt];
      maxVal[rt << 1 | 1].first += sign[rt];

      sumVal[rt << 1] += sign[rt] * Num(ranges[rt << 1]);
      sumVal[rt << 1 | 1] += sign[rt] * Num(ranges[rt << 1 | 1]);

      sign[rt] = 0;
    }
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    ranges[rt] = {l, r};
    if (l == r) {
      sumVal[rt] = str[l];  // 如果 str 没有复制一份，则需要注意边界是否越界
      minVal[rt] = maxVal[rt] = {str[l], l};
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, int R, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      sign[rt] += add;
      minVal[rt].first += add;
      maxVal[rt].first += add;
      sumVal[rt] += add * Num(ranges[rt]);
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
    PushUp(rt, l, r);
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
    pair<ll, int> ret = {__LONG_LONG_MAX__, 0};  // 求最小值，初始值设置为最大值
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
  int longestBalanced(const vector<int>& a) {
    int n = (int)a.size();
    segTree.Init(n);
    segTree.Build();
    int ans = 0;
    unordered_map<int, int> lastPos;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
      const int x = a[i - 1];
      const int v = (x & 1) ? 1 : -1;
      if (lastPos.count(x)) {
        segTree.Update(lastPos[x], i - 1, -v); // 区间前缀和删除之前的数字
        sum -= v;
      }
      lastPos[x] = i;
      sum += v;
      segTree.Update(i, i, sum); // 单点更新当前答案
      if (sum == 0) { // 特殊判断，整个区间都是答案
        ans = max(ans, i);
        continue;
      }
      int l = 1, r = i;  // i 肯定是答案
      while (l < r) {
        const int mid = (l + r) >> 1;
        auto [minVal, minPos] = segTree.QueryMin(1, mid);
        auto [maxVal, maxPos] = segTree.QueryMax(1, mid);
        if (minVal <= sum && sum <= maxVal) {
          r = mid;
        } else {
          l = mid + 1;
        }
      }
      ans = max(ans, i - r);
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

int main() { return 0; }

#endif