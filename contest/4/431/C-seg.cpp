
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

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
  vector<tuple<ll, ll, ll>> sumVal;  // <L,R,sum>
  vector<tuple<ll, ll, ll>> str;     // <L,R, V>

  void Init(vector<vector<int>>& str_, const ll default_val = 0) {
    maxNM = str_.size();
    sumVal.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1);
    for (size_t i = 0; i < str_.size(); i++) {
      str[i + 1] = {str_[i][0], str_[i][1], str_[i][2]};
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    ll L = get<0>(sumVal[rt << 1]);
    ll R = get<1>(sumVal[rt << 1 | 1]);
    ll V = get<2>(sumVal[rt << 1]) + get<2>(sumVal[rt << 1 | 1]);
    sumVal[rt] = {L, R, V};
  }

  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      auto [L, R, V] = str[l];
      sumVal[rt] = {L, R, V * (R - L + 1)};
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }

  ll QuerySum(ll L, ll R, int l = 1, int r = maxNM, int rt = 1) {
    const auto [PL, PR, PS] = sumVal[rt];
    if (L <= PL && PR <= R) {  // 包含
      return PS;
    }
    if (l == r) {  // 叶子不包含，部分相交
      const auto [PL, PR, PV] = str[l];
      if (L <= PL) {  // 前缀
        return PV * (min(R, PR) - PL + 1);
      } else {  // 非前缀, 包括后缀 与 包含
        return PV * (min(R, PR) - max(PL, L) + 1);
      }
    }
    int m = (l + r) >> 1;

    ll ret = 0;
    if (L <= get<1>(str[m])) {
      ret += QuerySum(L, R, lson);
    }
    if (get<1>(str[m]) < R) {
      ret += QuerySum(L, R, rson);
    }
    return ret;
  }
};

SegTree segTree;
class Solution {
 public:
  ll maximumCoins(vector<vector<int>>& coins, int k) {
    sort(coins.begin(), coins.end());

    segTree.Init(coins);
    segTree.Build();

    ll ans = 0;
    for (auto& coin : coins) {
      int l = coin[0];
      int r = coin[1];
      ans = max(ans, segTree.QuerySum(l, l + k - 1));
      ans = max(ans, segTree.QuerySum(r - k + 1, r));
    }
    return ans;
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<vector<int>> coins, int k, ll ans) {  //
  TEST_SMP2(Solution, maximumCoins, ans, coins, k);
}

int main() {
  Test({{35, 37, 15},
        {3, 9, 1},
        {31, 33, 20},
        {10, 15, 6},
        {1, 2, 5},
        {38, 39, 8},
        {20, 23, 16},
        {48, 49, 3},
        {40, 43, 4},
        {29, 30, 16}},
       42, 282);
  return 0;
}

#endif