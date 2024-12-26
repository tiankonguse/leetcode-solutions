
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
#include <bits/stdc++.h>
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
  vector<ll> maxVal;  // 记录最值的位置

  void Init(int n, const ll default_val = 0) {
    maxNM = n + 1;
    maxVal.resize(maxNM << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
  }
  int Num(pair<ll, ll> p) { return p.second - p.first + 1; }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      maxVal[rt] = 0;
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      maxVal[rt] += add;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, add, lson);
    if (L > m) Update(L, add, rson);
    PushUp(rt, l, r);
  }
  ll QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L == 0 || R == 0) return 0;
    if (L <= l && r <= R) {
      return maxVal[rt];
    }
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
class Solution {
 public:
  int maxEnvelopes(vector<vector<int>>& envelopes) {  //
    segTree.Init(maxn);
    segTree.Build();
    sort(envelopes.begin(), envelopes.end(), [](auto& a, auto& b) {
      if (a[0] == b[0]) {
        return a[1] > b[1];
      } else {
        return a[0] < b[0];
      }
    });

    int ans = 0;
    for (auto& v : envelopes) {
      const int y = v[1];
      //[1, y-1]
      const int newVal = segTree.QueryMax(1, y - 1) + 1;
      const int nowVal = segTree.QueryMax(y, y);
      ans = max(ans, newVal);
      if (newVal > nowVal) {
        segTree.Update(y, newVal - nowVal);
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<vector<int>>& envelopes, const int& ans) {
  TEST_SMP1(Solution, maxEnvelopes, ans, envelopes);
}

int main() {
  vector<vector<int>> envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
  Test(envelopes, 3);
  envelopes = {{1, 1}, {1, 1}, {1, 1}};
  Test(envelopes, 1);
  envelopes = {{4, 5}, {4, 6}, {6, 7}, {2, 3}, {1, 1}};
  Test(envelopes, 4);
  return 0;
}

#endif