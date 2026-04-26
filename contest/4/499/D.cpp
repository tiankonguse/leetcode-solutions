
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
// 超出时间限制 947 / 958 个通过的测试用例©leetcode
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
  vector<ll> maxVal;  // 记录最值的位置

  void Init(int n, const ll default_val = 0) {
    maxNM = n + 1;
    maxVal.resize(maxNM << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
  }
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
  void TryUpdate(int L, ll val, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      maxVal[rt] = max(maxVal[rt], val);
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) TryUpdate(L, val, lson);
    if (L > m) TryUpdate(L, val, rson);
    PushUp(rt, l, r);
  }
  ll QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
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

const int maxVal = 1e5 + 10;
SegTree segTree[2];
ll dp[maxVal][2];
class Solution {
 public:
  ll maxAlternatingSum(vector<int>& nums, int k) {
    int n = nums.size();
    segTree[0].Init(maxVal);
    segTree[1].Init(maxVal);
    segTree[0].Build();
    segTree[1].Build();

    for (int i = 0; i < n; ++i) {
      const int val = nums[i];
      dp[i][0] = val;
      dp[i][1] = val;
      if (i >= k) {
        if (val < maxVal - 1) {
          dp[i][0] += segTree[1].QueryMax(val + 1, maxVal);
        }
        if (val > 1) {
          dp[i][1] += segTree[0].QueryMax(1, val - 1);
        }
      }
      if (i >= k - 1) {
        const int offset = i - k + 1;
        const int val = nums[offset];
        segTree[0].TryUpdate(val, dp[offset][0]);
        segTree[1].TryUpdate(val, dp[offset][1]);
      }
    }
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
      ans = max(ans, max(dp[i][0], dp[i][1]));
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