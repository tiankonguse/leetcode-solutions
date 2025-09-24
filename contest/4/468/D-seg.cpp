
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
const int maxn = 5e4 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
enum { UP = 0, Down = 1 };
int leftDownVal[maxn << 2];      // 记录最值的位置
int rightDownVal[maxn << 2];     // 记录最值的位置
int leftUpVal[maxn << 2];        // 记录最值的位置
int rightUpVal[maxn << 2];       // 记录最值的位置
ll sumUpVal[maxn << 2];          // 记录区间和
ll sumDownVal[maxn << 2];        // 记录区间和
pair<int, int> sign[maxn << 2];  // <UP/Down, val>
pair<int, int> rangeslr[maxn << 2];
int str[maxn];  //
inline ll Num(const pair<ll, ll>& p) { return p.second - p.first + 1; }
ll Init(vector<int>& str_) {
  maxNM = str_.size();

  int maxVal = str_.front();
  int minVal = str_.front();
  for (int i = 0; i < str_.size(); i++) {
    maxVal = max(maxVal, str_[i]);
    minVal = min(minVal, str_[i]);
    str[i + 1] = str_[i];
  }
  return maxVal - minVal + 1;
}
// 合并函数，按需进行合并
inline void PushUp(int rt, int l, int r) {
  leftDownVal[rt] = min(leftDownVal[rt << 1], leftDownVal[rt << 1 | 1]);
  rightDownVal[rt] = max(rightDownVal[rt << 1], rightDownVal[rt << 1 | 1]);
  leftUpVal[rt] = max(leftUpVal[rt << 1], leftUpVal[rt << 1 | 1]);
  rightUpVal[rt] = min(rightUpVal[rt << 1], rightUpVal[rt << 1 | 1]);
  sumUpVal[rt] = sumUpVal[rt << 1] + sumUpVal[rt << 1 | 1];
  sumDownVal[rt] = sumDownVal[rt << 1] + sumDownVal[rt << 1 | 1];
}
inline void PushDown(int rt) {
  auto [dir, setVal] = sign[rt];
  if (setVal != -1) {
    sign[rt << 1] = sign[rt << 1 | 1] = sign[rt];
    if (dir == UP) {
      leftUpVal[rt << 1] = leftUpVal[rt << 1 | 1] = setVal;
      rightUpVal[rt << 1] = rightUpVal[rt << 1 | 1] = setVal;
      sumUpVal[rt << 1] = setVal * Num(rangeslr[rt << 1]);
      sumUpVal[rt << 1 | 1] = setVal * Num(rangeslr[rt << 1 | 1]);
    } else {
      leftDownVal[rt << 1] = leftDownVal[rt << 1 | 1] = setVal;
      rightDownVal[rt << 1] = rightDownVal[rt << 1 | 1] = setVal;
      sumDownVal[rt << 1] = setVal * Num(rangeslr[rt << 1]);
      sumDownVal[rt << 1 | 1] = setVal * Num(rangeslr[rt << 1 | 1]);
    }

    sign[rt].second = -1;
  }
}
void Build(int l = 1, int r = maxNM, int rt = 1) {
  sign[rt] = {-1, -1};
  rangeslr[rt] = {l, r};
  if (l == r) {
    sumUpVal[rt] = sumDownVal[rt] = leftDownVal[rt] = rightDownVal[rt] = leftUpVal[rt] = rightUpVal[rt] = str[l];
    return;
  }
  int m = (l + r) >> 1;
  Build(lson);
  Build(rson);
  PushUp(rt, l, r);
}
void Update(int L, int R, ll setVal, int l = 1, int r = maxNM, int rt = 1) {
  if (L <= l && r <= R) {
    if (setVal > rightUpVal[rt]) {    // 更新最大值
      if (setVal >= leftUpVal[rt]) {  // 更新所有的最大值
        sign[rt] = {UP, setVal};
        leftUpVal[rt] = rightUpVal[rt] = setVal;
        sumUpVal[rt] = setVal * Num(rangeslr[rt]);
        return;
      } else {
        // 部分需要更新，继续递归
      }
    } else if (setVal < rightDownVal[rt]) {  // 更新最小值
      if (setVal < leftDownVal[rt]) {        // 更新所有的最小值
        sign[rt] = {Down, setVal};
        leftDownVal[rt] = rightDownVal[rt] = setVal;
        sumDownVal[rt] = setVal * Num(rangeslr[rt]);
        return;
      } else {
        // 部分需要更新，继续递归
      }
    } else {
      return;  // 都不需要更新
    }
  }
  PushDown(rt);
  int m = (l + r) >> 1;
  if (L <= m) Update(L, R, setVal, lson);
  if (R > m) Update(L, R, setVal, rson);
  PushUp(rt, l, r);
}

// 大于等于 d 的子数组的个数与值的和，个数超过K时马上返回
pair<ll, ll> SearchAndCheck(const ll d, const ll K, int L, int R, int l = 1, int r = maxNM, int rt = 1) {
  if (L <= l && r <= R) {                          // 完整的查询区间
    if (rightUpVal[rt] - rightDownVal[rt] >= d) {  // 整个区间都满足条件，直接返回
      return {Num(rangeslr[rt]), sumUpVal[rt] - sumDownVal[rt]};
    }
    if (leftUpVal[rt] - leftDownVal[rt] < d) {  // 整个区间都不满足条件，直接返回
      return {0, 0};
    }
    // 其他情况需要递归查询
  }
  PushDown(rt);
  int m = (l + r) >> 1;
  ll num = 0, sum = 0;
  if (L <= m) {
    auto [numChild, sumChild] = SearchAndCheck(d, K, L, R, lson);
    num += numChild;
    sum += sumChild;
    if (num >= K) {
      return {num, sum};  // 剪枝，查询阶段已经满足条件
    }
  }
  if (m < R) {
    auto [numChild, sumChild] = SearchAndCheck(d, K - num, L, R, rson);
    num += numChild;
    sum += sumChild;
    if (num >= K) {
      return {num, sum};  // 剪枝，查询阶段已经满足条件
    }
  }
  return {num, sum};
}

class Solution {
  ll n;
  vector<int> nums;
  pair<ll, ll> SearchAndCheckAll(const ll d, const ll K) {  // 大于等于 d 的子数组的个数与值的和，个数超过K时马上返回
    // MyPrintf("d=%lld K=%lld\n", d, K);
    Build();
    ll num = 0, sum = 0;
    for (int i = 1; i <= n; i++) {
      const ll nowVal = nums[i - 1];
      Update(1, i, nowVal);
      const auto [numChild, sumChild] = SearchAndCheck(d, K - num, 1, i);
      num += numChild;
      sum += sumChild;
      // MyPrintf("i=%d, num=%lld, sum=%lld numChild=%lld sumChild=%lld\n", i, num, sum, numChild, sumChild);
      if (num >= K) {
        return {num, sum};  // 剪枝，查询阶段已经满足条件
      }
    }
    return {num, sum};
  }

 public:
  ll maxTotalValue(vector<int>& nums_, const int k) {  //
    nums.swap(nums_);
    n = nums.size();
    if (n == 1) return 0;
    const ll maxDis = Init(nums);

    // MyPrintf("maxVal=%lld, minVal=%lld, maxDis=%lld\n", maxVal, minVal, maxDis);
    // MyPrintf("k=%d\n", k);

    ll l = 0, r = maxDis;  // [l, r)
    while (l < r) {
      const ll mid = (l + r) / 2;
      if (SearchAndCheckAll(mid, k).first >= k) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    // MyPrintf("l=%lld, r=%lld\n", l, r);
    const auto [numR, sumR] = SearchAndCheckAll(r, INT64_MAX);
    // MyPrintf("numR=%lld, sumR=%lld\n", numR, sumR);
    return sumR + (k - numR) * (r - 1);
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