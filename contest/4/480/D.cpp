
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
  vector<ll> sumVal;    // 区间内，相邻相等的个数
  vector<ll> leftVal;   // 区间内，最左边的值
  vector<ll> rightVal;  // 区间内，最右边的值
  vector<ll> str;

  void Init(const vector<ll>& str_, const ll default_val = 0) {
    maxNM = str_.size() + 1;
    sumVal.resize(maxNM << 2);
    leftVal.resize(maxNM << 2);
    rightVal.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1, default_val);
    for (int i = 0; i < str_.size(); i++) {
      str[i + 1] = str_[i];
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    leftVal[rt] = leftVal[rt << 1];
    rightVal[rt] = rightVal[rt << 1 | 1];
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
    if (rightVal[rt << 1] == leftVal[rt << 1 | 1]) {
      sumVal[rt]++;
    }
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      sumVal[rt] = 0;  // 如果 str 没有复制一份，则需要注意边界是否越界
      leftVal[rt] = rightVal[rt] = str[l];
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, ll val, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      sumVal[rt] = 0;  // 单点更新，不存在相同值
      leftVal[rt] = rightVal[rt] = val;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, val, lson);
    if (L > m) Update(L, val, rson);
    PushUp(rt, l, r);
  }

  // 返回区间内 sum, leftVal, rightVal
  tuple<ll, ll, ll> Query(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return {sumVal[rt], leftVal[rt], rightVal[rt]};
    }
    int m = (l + r) >> 1;
    if (R <= m) {  // 区间都在左边
      return Query(L, R, l, m, rt << 1);
    } else if (m < L) {  // 区间都在右边
      return Query(L, R, m + 1, r, rt << 1 | 1);
    } else {  // 区间跨左右
      auto [leftSum, leftLeft, leftRight] = Query(L, R, l, m, rt << 1);
      auto [rightSum, rightLeft, rightRight] = Query(L, R, m + 1, r, rt << 1 | 1);
      return {leftSum + rightSum + (leftRight == rightLeft), leftLeft, rightRight};
    }
  }
};

SegTree segTree;
class Solution {
 public:
  vector<int> minDeletions(const string& s, vector<vector<int>>& queries) {
    int n = s.size();
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
      nums[i] = s[i] == 'A';
    }
    segTree.Init(nums);
    segTree.Build();

    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      int op = q[0];
      if (op == 1) {
        int l = q[1] + 1;
        nums[l - 1] = 1 - nums[l - 1];  // 翻转
        segTree.Update(l, nums[l - 1]);
      } else {
        int l = q[1] + 1, r = q[2] + 1;
        auto [sum, left, right] = segTree.Query(l, r);
        ans.push_back(sum);
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