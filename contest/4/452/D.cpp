
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
#include <bits/stdc++.h>
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
  vector<ll> sign;
  vector<ll> maxVal;  // 记录最值的位置

  void Init(int n, const ll default_val = 0) {
    maxNM = n + 1;
    sign.resize(maxNM << 2, 0);
    maxVal.resize(maxNM << 2, 0);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) { maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]); }
  void PushDown(int rt) {
    if (sign[rt]) {
      sign[rt << 1] += sign[rt];
      sign[rt << 1 | 1] += sign[rt];

      maxVal[rt << 1] += sign[rt];
      maxVal[rt << 1 | 1] += sign[rt];

      sign[rt] = 0;
    }
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    if (l == r) {
      maxVal[rt] = 0;
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
      maxVal[rt] += add;
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
    PushUp(rt, l, r);
  }
  ll QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxVal[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    ll ret = 0;
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

const int N = 1e5 + 10;
const int M = 1e4;
bool is[N];
int prm[M];
int K = 0;
/*
1e4 3.732020845644619
1e5 4.053948940531981
1e6 4.316983346365776
1e7 4.539375767702223
*/
int getprm() {
  if (K != 0) return K;
  // O(n log log n)
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  memset(is, 1, sizeof(is));
  prm[k++] = 2;
  is[0] = is[1] = 0;
  for (i = 4; i < N; i += 2) is[i] = 0;
  for (i = 3; i < e; i += 2) {
    if (is[i]) {
      prm[k++] = i;
      for (int s = i + i, j = i * i; j < N; j += s) is[j] = 0;
    }
  }
  for (; i < N; i += 2)
    if (is[i]) prm[k++] = i;
  return K = k;
}

class Solution {
 public:
  vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
    getprm();
    // MyPrintf("k=%d\n", K);
    int n = nums.size();
    segTree.Init(n);
    segTree.Build();
    unordered_map<ll, set<int>> pos;
    for (int i = 1; i <= n; i++) {
      int v = nums[i - 1];
      if (is[v]) {
        pos[v].insert(i);
      }
    }
    for (auto& [v, ps] : pos) {
      if (ps.size() == 1) continue;
      int l = *ps.begin();
      int r = *ps.rbegin();
      segTree.Update(l, r - 1, 1);
    }
    int ansNum = pos.size();
    auto Update = [&](int p, int v, int flag) {
      auto& ps = pos[v];
      if (ps.size() > 1) {
        int l = *ps.begin();
        int r = *ps.rbegin();
        segTree.Update(l, r - 1, -1);
      }
      if (flag == 1) {
        if (ps.empty()) ansNum++;
        ps.insert(p);
      } else {
        ps.erase(p);
        if (ps.empty()) ansNum--;
      }
      if (ps.size() > 1) {
        int l = *ps.begin();
        int r = *ps.rbegin();
        segTree.Update(l, r - 1, 1);
      }
    };
    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      int i = q[0] + 1;
      int oldVal = nums[i - 1];
      int newVal = q[1];
      nums[i - 1] = newVal;
      if (is[oldVal]) {
        Update(i, oldVal, -1);
      }
      if (is[newVal]) {
        Update(i, newVal, 1);
      }
      ans.push_back(ansNum + segTree.QueryMax(1, n));
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