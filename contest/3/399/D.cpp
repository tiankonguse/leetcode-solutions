// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
struct SegTree {
  vector<ll> sumVal;
  vector<ll> sumFirst;  // 不选第一个的最优答案
  vector<ll> sumLast;   // 不选最后一个的最优答案
  vector<ll> sumMid;    // 两边都不选的最优答案

  void Init(int n) {
    maxNM = n;
    sumVal.resize(maxNM << 2, 0);
    sumFirst.resize(maxNM << 2, 0);
    sumLast.resize(maxNM << 2, 0);
    sumMid.resize(maxNM << 2, 0);
  }

  void PushUp(int l, int r, int rt) {
    int m = (l + r) >> 1;
    sumVal[rt] = 0;
    // (l, m) + (m+2, r)
    sumVal[rt] = max(sumVal[rt], sumVal[rt << 1] + sumFirst[rt << 1 | 1]);
    // (l, m-1) + (m+1, r)
    sumVal[rt] = max(sumVal[rt], sumLast[rt << 1] + sumVal[rt << 1 | 1]);

    sumFirst[rt] = 0;
    // (l+1, m) + (m+2, r)
    sumFirst[rt] = max(sumFirst[rt], sumFirst[rt << 1] + sumFirst[rt << 1 | 1]);
    // (l+1, m-1) + (m+1, r)
    sumFirst[rt] = max(sumFirst[rt], sumMid[rt << 1] + sumVal[rt << 1 | 1]);

    sumLast[rt] = 0;
    // (l, m) + (m+2, r-1)
    sumLast[rt] = max(sumLast[rt], sumVal[rt << 1] + sumMid[rt << 1 | 1]);
    // (l, m-1) + (m+1, r-1)
    sumLast[rt] = max(sumLast[rt], sumLast[rt << 1] + sumLast[rt << 1 | 1]);

    sumMid[rt] = 0;
    // (l+1, m) + (m+2, r-1)
    sumMid[rt] = max(sumMid[rt], sumFirst[rt << 1] + sumMid[rt << 1 | 1]);
    // (l+1, m-1) + (m+1, r-1)
    sumMid[rt] = max(sumMid[rt], sumMid[rt << 1] + sumLast[rt << 1 | 1]);
  }
  void Build(vector<int>& nums, int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      sumVal[rt] = max(nums[l - 1], 0);
      sumFirst[rt] = sumLast[rt] = sumMid[rt] = 0;  // 只有一个，不选择就是空
      return;
    }
    int m = (l + r) >> 1;
    Build(nums, lson);
    Build(nums, rson);
    PushUp(l, r, rt);
  }
  void Update(int x, int v, int l = 1, int r = maxNM, int rt = 1) {
    if (x <= l && r <= x) {  // 单点更新
      sumVal[rt] = max(v, 0);
      sumFirst[rt] = sumLast[rt] = sumMid[rt] = 0;  // 只有一个，不选择就是空
      return;
    }
    int m = (l + r) >> 1;
    if (x <= m) Update(x, v, lson);
    if (x > m) Update(x, v, rson);
    PushUp(l, r, rt);
  }
  ll QuerySum(const int L, const int R, const int l = 1, const int r = maxNM,
              const int rt = 1) {
    if (L > R) return 0;  // 非法，按 0 处理
    if (L == l && R == r) {
      return sumVal[rt];
    }
    if (L - 1 == l && R == r) {
      return sumFirst[rt];
    }
    if (L == l && R + 1 == r) {
      return sumLast[rt];
    }
    if (L - 1 == l && R + 1 == r) {
      return sumMid[rt];
    }

    int m = (l + r) >> 1;
    if (R <= m) {  // 都在左边
      return QuerySum(L, R, lson);
    } else if (L > m) {  // 都在右边
      return QuerySum(L, R, rson);
    } else {  // 分为两段
      return max(QuerySum(L, m, lson) + QuerySum(m + 2, R, rson),
                 QuerySum(L, m - 1, lson) + QuerySum(m + 1, R, rson));
    }
  }
};

SegTree segTree;
class Solution {
 public:
  int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
    int n = nums.size();
    segTree.Init(n);
    segTree.Build(nums);

    ll ans = 0;
    for (auto& v : queries) {
      const int pos = v[0] + 1;
      const ll x = v[1];
      segTree.Update(pos, x);
      ll tmp = segTree.QuerySum(1, n);
      // printf("tm=%lld\n", tmp);
      ans = (ans + tmp) % mod;
    }
    return ans;
  }
};