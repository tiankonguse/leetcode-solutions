
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
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
struct SegTree {
  vector<int> allVal;
  vector<vector<ll>> preVal;  // 记录最值的位置
  vector<ll> str;
  int k;

  void Init(const vector<int>& str_, const int k) {
    this->k = k;
    maxNM = str_.size() + 1;
    allVal.clear();
    allVal.resize(maxNM << 2);
    preVal.clear();
    preVal.resize(maxNM << 2, vector<ll>(k, 0));
    str.resize(maxNM + 1, 0);
    for (int i = 0; i < str_.size(); i++) {
      str[i + 1] = str_[i] % k;
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    allVal[rt] = (allVal[rt << 1] * allVal[rt << 1 | 1]) % k;

    for (int i = 0; i < k; i++) {
      preVal[rt][i] = preVal[rt << 1][i];
    }
    int leftAllVal = allVal[rt << 1];
    for (int i = 0; i < k; i++) {
      preVal[rt][(i * leftAllVal) % k] += preVal[rt << 1 | 1][i];
    }
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      int val = str[l] % k;
      allVal[rt] = val;
      preVal[rt].assign(k, 0);
      preVal[rt][val] = 1;
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, ll val, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      allVal[rt] = val;
      preVal[rt].assign(k, 0);
      preVal[rt][val] = 1;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, val, lson);
    if (L > m) Update(L, val, rson);
    PushUp(rt, l, r);
  }
  ll QueryAll(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return allVal[rt];
    }
    int m = (l + r) >> 1;
    ll ret = 1;
    if (L <= m) {
      ret = (ret * QueryAll(L, R, lson)) % k;
    }
    if (m < R) {
      ret = (ret * QueryAll(L, R, rson)) % k;
    }
    return ret;
  }
  ll QueryPre(int L, int R, int val, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return preVal[rt][val];
    }
    int m = (l + r) >> 1;
    ll ret = 0;
    ll leftAll = -1; // 做区间的乘积，-1 代表不存在做区间
    if (L <= m) {
      ret += QueryPre(L, R, val, lson);
      leftAll = QueryAll(L, R, lson);
    }
    if (m < R) {
      if (leftAll == -1) {
        ret += QueryPre(L, R, val, rson);
      } else {
        // 利用乘法逆元，求出所有合法的右区间目标乘积
        for (int x = 0; x < k; x++) {
          if (leftAll * x % k == val) {
            ret += QueryPre(L, R, x, rson);
          }
        }
      }
    }
    return ret;
  }
};
SegTree segTree;
class Solution {
 public:
  vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
    int n = nums.size();
    segTree.Init(nums, k);
    segTree.Build();

    vector<int> results;
    results.reserve(queries.size());
    // queries[i] = [indexi, valuei, starti, xi]
    for (const auto& query : queries) {
      int index = query[0];
      int value = query[1] % k;
      int start = query[2];
      int x = query[3];

      segTree.Update(index + 1, value);  // 1-based
      MyPrintf("Update %d %d\n", index + 1, value);
      MyPrintf("QueryPre [%d %d] x=%d\n", start + 1, n, x);
      ll ans = segTree.QueryPre(start + 1, n, x);  // 1-based
      results.push_back(ans);
    }
    return results;
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