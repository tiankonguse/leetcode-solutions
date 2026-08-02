
#ifdef USACO_LOCAL_JUDGE
// 599 / 601 个通过的测试用例
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
  vector<ll> sumVal;

  void Init(int n) {
    maxNM = n + 1;
    sumVal.resize(maxNM << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
  }
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
  void Add(int L, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      sumVal[rt] += add;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Add(L, add, lson);
    if (L > m) Add(L, add, rson);
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
SegTree segTree;
class Solution {
  map<ll, int> H;
  void Init(const vector<int>& nums, ll a, ll b) {
    H.clear();
    int n = nums.size();
    H[0] = 0;
    ll val = 0;
    for (int i = 0; i < n; i++) {
      if (nums[i] % 2 == 0) {
        val -= b;
      } else {
        val += a;
      }
      H[val] = 0;
    }
    int index = 0;
    for (auto& [val, offset] : H) {
      offset = ++index;
    }
  }

 public:
  ll countRatioSubarrays(vector<int>& nums, ll a, ll b) {
    Init(nums, a, b); // 离散化
    int n = nums.size();
    ll ans = 0;

    segTree.Init(n + 1);
    segTree.Build();

    ll val = 0;
    segTree.Add(H[0], 1);
    for (int i = 0; i < n; i++) {
      if (nums[i] % 2 == 0) {
        val -= b;
      } else {
        val += a;
      }
      ll offset = H[val];
      ans += segTree.QuerySum(1, offset);
      segTree.Add(offset, 1);
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