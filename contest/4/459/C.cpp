
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
线段树：单点更新，区间查询
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
// const int maxn = 1e5 + 10;
// const int kMaxVal = 10e8;

int maxNM;
typedef long long ll;
struct SegTree {
  vector<ll> sumVal;

  void Init(int n, const ll default_val = 0) {
    maxNM = n + 1;
    sumVal.resize(maxNM << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) { sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1]; }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      sumVal[rt] = 0;
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
};
// 596 / 600 个通过的测试用例©leetcode

const int maxDepth = 6;
const ll kPreCalDepth = 64;
SegTree segTree[maxDepth];
vector<int> dpDepth;

class Solution {
  void InitDepth() {
    dpDepth.resize(kPreCalDepth);
    dpDepth[0] = 0;
    dpDepth[1] = 0;
    for (ll i = 2; i < kPreCalDepth; i++) {
      int pre = __builtin_popcountll(i);
      if (pre == 1) {
        dpDepth[i] = 1;
      } else {
        dpDepth[i] = dpDepth[pre] + 1;
      }
    }
  }
  int GetDepth(const ll v) {
    if (v < kPreCalDepth) {
      return dpDepth[v];
    }
    const int pre = __builtin_popcountll(v);
    if (pre == 1) {
      return 1;
    }
    return dpDepth[pre] + 1;
  }

 public:
  vector<int> popcountDepth(vector<ll>& nums, vector<vector<ll>>& queries) {  //
    const int n = nums.size();
    InitDepth();
    for (int i = 0; i < maxDepth; i++) {
      segTree[i].Init(n);
      segTree[i].Build();
    }
    for (int i = 1; i <= n; i++) {
      const ll v = nums[i - 1];
      const int d = GetDepth(v);
      if (d < maxDepth) {
        segTree[d].Update(i, 1);
      }
    }
    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      const ll t = q[0];
      if (t == 1) {
        const ll l = q[1] + 1, r = q[2] + 1, k = q[3];
        if (k >= maxDepth) {
          ans.push_back(0);
        } else {
          ans.push_back(segTree[k].QuerySum(l, r));
        }
      } else {
        const ll idx = q[1] + 1, newVal = q[2];
        const ll oldVal = nums[idx - 1];
        const int oldDepth = GetDepth(oldVal);
        const int newDepth = GetDepth(newVal);

        if (oldDepth < maxDepth) segTree[GetDepth(oldVal)].Update(idx, -1);
        if (newDepth < maxDepth) segTree[GetDepth(newVal)].Update(idx, 1);
        nums[idx - 1] = newVal;
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif