
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
#include <bits/stdc++.h>
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
  vector<ll> sumVal;
  vector<ll> countVal;

  void Init(int n) {
    maxNM = n + 1;
    // sumVal.clear();
    sumVal.resize(maxn << 2);
    countVal.resize(maxn << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
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
  void Update(int L, ll addSum, ll addCount, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      sumVal[rt] += addSum;
      countVal[rt] += addCount;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, addSum, addCount, lson);
    if (L > m) Update(L, addSum, addCount, rson);
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
ll h[maxn];
ll dp2[maxn];
ll dp[maxn][16];
class Solution {
  // vector<vector<ll>> dp;
  int x;

  unordered_map<ll, int> H;
  ll sum = 0;

  ll Search() {
    // 如果 x 是 奇数，则中位数是 x/2+1
    // 如果 x 是 偶数，则中位数是 x/2
    int midX = (x + 1) / 2;

    int l = 1, r = H.size();
    while (l < r) {
      int m = (l + r) >> 1;
      if (segTree.QueryCount(1, m) >= midX) {
        r = m;
      } else {
        l = m + 1;
      }
    }
    ll minV = h[l - 1];
    ll lessNum = segTree.QueryCount(1, l);
    ll lessSum = segTree.QuerySum(1, l);
    ll moreNum = x - lessNum;
    ll moreSum = sum - lessSum;
    return moreSum - moreNum * minV + minV * lessNum - lessSum;
  }

 public:
  ll minOperations(vector<int>& nums, int x_, int k) {
    x = x_;
    if (x == 1) return 0;

    int n = nums.size();

    // 初始化线段树，离散化
    segTree.Init(n);
    segTree.Build();

    // 离散化
    H.clear();
    for (auto v : nums) {
      H[v] = 0;
    }
    int idx = 0;
    for (auto& [kk, vv] : H) {
      h[idx] = kk;
      idx++;
    }
    sort(h, h + idx);
    for (int i = 0; i < idx; i++) {
      H[h[i]] = i + 1;
    }
    // MyPrintf("h.size()=%d\n", h.size());

    // 滑动窗口计算 dp2 的值
    sum = 0;
    // MyPrintf("count=%lld sum=%lld\n", segTreeCount.QuerySum(1, H.size()), segTreeSum.QuerySum(1, H.size()));
    for (int i = 1; i <= n; i++) {
      const int v = nums[i - 1];
      const int pos = H[v];

      // MyPrintf("i=%d\n", i);
      segTree.Update(pos, nums[i - 1], 1);
      sum += nums[i - 1];
      // MyPrintf("count=%lld sum=%lld\n", segTreeCount.QuerySum(1, H.size()), segTreeSum.QuerySum(1, H.size()));
      if (i < x) {
        continue;
      }
      dp2[i] = Search();
      // MyPrintf("dp2[%d] = %lld\n", i, dp2[i]);
      const int pos2 = H[nums[i - x]];
      segTree.Update(pos2, -nums[i - x], -1);
      sum -= nums[i - x];
    }

    // dp.resize(n + 1, vector<ll>(k + 1, __LONG_LONG_MAX__));
    for (int i = 0; i <= n; i++) {
      dp[i][0] = 0;
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= k; j++) {
        if (i < j * x) {
          dp[i][j] = __LONG_LONG_MAX__;
        } else {
          dp[i][j] = min(dp[i - 1][j], dp[i - x][j - 1] + dp2[i]);
        }
      }
    }
    return dp[n][k];
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif