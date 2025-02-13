
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
    sign.clear();
    sign.resize(maxNM << 2, 0);
    maxVal.clear();
    maxVal.resize(maxNM << 2, 0);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
  }
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

/*


a1 a2 a3 a4 ... an
b1 b2 b3 b4 ... bn

a[j] + nums[i,j]

=k: 前面都不变
=x: 前面都加1


*/
SegTree segTree;
class Solution {
 public:
  int maxFrequency(vector<int>& nums, const int k) {
    int n = nums.size();
    int ans = 0;
    vector<int> stats(51, 0);
    for (auto v : nums) {
      stats[v]++;
    }

    vector<int> suffixSum(n + 2, 0);
    for (int i = n; i >= 1; i--) {
      int v = nums[i - 1];
      suffixSum[i] = suffixSum[i + 1];
      if (v == k) {
        suffixSum[i]++;
      }
    }

    ans = stats[k];
    for (int i = 1; i <= 50; i++) {
      if (i == k || stats[i] == 0) continue;
      segTree.Init(n);
      segTree.Build();
      int kNum = 0;
      for (int j = 1; j <= n; j++) {
        int v = nums[j - 1];
        if (v == k) {
          kNum++;
          segTree.Update(j, j, kNum - 1);
        } else if (v == i) {
          if (j > 1) {
            segTree.Update(1, j - 1, 1);
          }
          segTree.Update(j, j, kNum + 1);
        } else {
          segTree.Update(j, j, kNum);
        }

        int tmpAns = segTree.QueryMax(1, j) + suffixSum[j + 1];
        ans = max(ans, tmpAns);
      }
    }
    return ans;
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