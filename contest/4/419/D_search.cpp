// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 0;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
/*
线段树：区间单点更新，修改查询
特征：不需要延迟标记与PushDown，log(N)的更新时间复杂度

输入数组： vector<int> str; [0, n-1]

SegTree segTree;
segTree.Init(str); // 内部会对数组进行右移，转化为 [1,n]
segTree.Build();
segTree.Update(l, val); // 单点 l 都加上 val, 数据范围 [1,n]
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
  vector<ll> sumVal;
  vector<ll> countVal;

  void Init(const ll n, const ll default_val = 0) {
    maxNM = n + 1;
    sumVal.resize(maxNM << 2);
    countVal.resize(maxNM << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
    countVal[rt] = countVal[rt << 1] + countVal[rt << 1 | 1];
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      sumVal[rt] = 0;
      countVal[rt] = 0;
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      sumVal[rt] += add;
      countVal[rt] = add > 0 ? 1 : 0;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, add, lson);
    if (L > m) Update(L, add, rson);
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
    return ret;
  }
  ll QueryCount(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return countVal[rt];
    }
    int m = (l + r) >> 1;
    ll ret = 0;
    if (L <= m) {
      ret += QueryCount(L, R, lson);
    }
    if (m < R) {
      ret += QueryCount(L, R, rson);
    }
    return ret;
  }
};
SegTree segTree;

class Solution {
  ll n;
  ll m;                     // 去重后个数
  unordered_map<ll, ll> C;  // 出现的次数
  unordered_map<ll, ll> h;  // 离线化
  ll H(const ll count, const ll v) { return count << 32 | v; }

  void Add(const ll v) {
    const ll oldNum = C[v];
    const ll oldIndex = h[H(oldNum, v)];
    C[v]++;
    const ll newNum = C[v];
    const ll newIndex = h[H(newNum, v)];

    if (oldNum > 0) {
      segTree.Update(oldIndex, -oldNum * v);
    }
    segTree.Update(newIndex, newNum * v);

    myprintf("all=%lld sum=%lld\n", segTree.QueryCount(1, m),
             segTree.QuerySum(1, m));
  }
  void Remove(const ll v) {
    const ll oldNum = C[v];
    const ll oldIndex = h[H(oldNum, v)];
    C[v]--;
    const ll newNum = C[v];
    const ll newIndex = h[H(newNum, v)];

    segTree.Update(oldIndex, -oldNum * v);
    if (newNum > 0) {
      segTree.Update(newIndex, newNum * v);
    }
  }
  ll Query(const ll x) {  //
    ll l = 1, r = m;      // [l, n]
    while (l < r) {
      const ll mid = (l + r) / 2;
      const ll count = segTree.QueryCount(mid, m);
      if (count > x) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    myprintf("r=%lld m=%lld all=%lld\n", r, m, segTree.QueryCount(1, m));
    return segTree.QuerySum(r, m);
  }

  void Init(vector<int>& nums, const int k, const int x) {  //
    n = nums.size();

    vector<ll> vals;
    vals.reserve(n * 2);
    ll l = 0, r = 0;  //[l, r)
    for (r = 0; r < k; r++) {
      const ll rv = nums[r];
      vals.push_back(H(C[rv], rv));
      C[rv]++;
      vals.push_back(H(C[rv], rv));
    }
    for (; r < n; r++, l++) {
      const ll lv = nums[l];
      C[lv]--;
      vals.push_back(H(C[lv], lv));

      const ll rv = nums[r];
      vals.push_back(H(C[rv], rv));
      C[rv]++;
      vals.push_back(H(C[rv], rv));
    }
    sort(vals.begin(), vals.end());

    m = 1;
    ll pre = -1;
    for (auto& v : vals) {
      if (v == pre) continue;
      pre = v;
      h[v] = m;
      m++;
    }

    C.clear();

    segTree.Init(m);  // 最多出现 m 次
    segTree.Build();
  }

 public:
  vector<ll> findXSum(vector<int>& nums, const int k, const int x) {
    Init(nums, k, x);

    vector<ll> ans;
    ans.reserve(n - k + 1);

    ll l = 0, r = 0;  //[l, r)
    for (r = 0; r < k; r++) {
      Add(nums[r]);
    }
    ans.push_back(Query(x));
    for (; r < n; r++, l++) {
      Remove(nums[l]);
      Add(nums[r]);
      ans.push_back(Query(x));
    }
    return ans;
  }
};