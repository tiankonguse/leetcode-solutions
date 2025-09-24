
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
  vector<ll> minVal;  // 记录最值的位置
  vector<ll> maxVal;  // 记录最值的位置
  vector<ll> sumVal;  // 记录区间和
  vector<ll> sign;
  vector<pair<ll, ll>> ranges;
  vector<ll> str;  //

  void Init(vector<int>& str_, const ll default_val = 0) {
    maxNM = str_.size() + 1;
    minVal.resize(maxNM << 2);
    maxVal.resize(maxNM << 2);
    sumVal.resize(maxNM << 2);
    sign.resize(maxNM << 2, -1);
    ranges.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1, default_val);
    for (int i = 0; i < str_.size(); i++) {
      str[i + 1] = str_[i];
    }
  }

  int Num(const pair<ll, ll>& p) { return p.second - p.first + 1; }
  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
  }
  void PushDown(int rt) {
    if (sign[rt] != -1) {
      sign[rt << 1] = sign[rt];
      sign[rt << 1 | 1] = sign[rt];

      minVal[rt << 1] = sign[rt];
      minVal[rt << 1 | 1] = sign[rt];

      maxVal[rt << 1] = sign[rt];
      maxVal[rt << 1 | 1] = sign[rt];

      sumVal[rt << 1] = sign[rt] * Num(ranges[rt << 1]);
      sumVal[rt << 1 | 1] = sign[rt] * Num(ranges[rt << 1 | 1]);

      sign[rt] = -1;
    }
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = -1;
    ranges[rt] = {l, r};
    if (l == r) {
      sumVal[rt] = minVal[rt] = maxVal[rt] = str[l];
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void UpdateMax(int L, int R, ll setVal, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      if (setVal <= minVal[rt]) return;
      if (setVal >= maxVal[rt]) {
        sign[rt] = setVal;  // 大于区间所有值，进行标记
        minVal[rt] = maxVal[rt] = setVal;
        sumVal[rt] = setVal * (r - l + 1);
        return;
      }
      // 其他情况需要递归更新
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) UpdateMax(L, R, setVal, lson);
    if (R > m) UpdateMax(L, R, setVal, rson);
    PushUp(rt, l, r);
  }

  void UpdateMin(int L, int R, ll setVal, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      if (setVal >= maxVal[rt]) return;
      if (setVal <= minVal[rt]) {
        sign[rt] = setVal;  // 大于区间所有值，进行标记
        minVal[rt] = maxVal[rt] = setVal;
        sumVal[rt] = setVal * (r - l + 1);
        return;
      }
      // 其他情况需要递归更新
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) UpdateMin(L, R, setVal, lson);
    if (R > m) UpdateMin(L, R, setVal, rson);
    PushUp(rt, l, r);
  }
  ll QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxVal[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    ll ret = -1;
    if (L <= m) {
      ret = max(ret, QueryMax(L, R, lson));
    }
    if (m < R) {
      ret = max(ret, QueryMax(L, R, rson));
    }
    return ret;
  }
  ll QueryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    ll ret = __LONG_LONG_MAX__;  // 求最小值，初始值设置为最大值
    if (L <= m) {
      ret = min(ret, QueryMin(L, R, lson));
    }
    if (m < R) {
      ret = min(ret, QueryMin(L, R, rson));
    }
    return ret;
  }
  ll QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return sumVal[rt];
    }
    PushDown(rt);
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

SegTree segTreeMax;
SegTree segTreeMin;
class Solution {
  ll n;
  vector<int> nums;
  pair<ll, ll> Search(ll d) {  // 大于等于 d 的子数组的个数与值的和
    segTreeMin.Init(nums);
    segTreeMin.Build();
    segTreeMax.Init(nums);
    segTreeMax.Build();

    ll num = 0;
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
      const ll nowVal = nums[i - 1];
      segTreeMax.UpdateMax(1, i, nowVal);
      segTreeMin.UpdateMin(1, i, nowVal);
      int l = 1, r = i + 1;  // [l, r)
      while (l < r) {
        int m = (l + r) / 2;
        if (segTreeMax.QuerySum(m, m) - segTreeMin.QuerySum(m, m) >= d) {
          l = m + 1;
        } else {
          r = m;
        }
      }
      if (r > 1) {
        num += r - 1;
        sum += segTreeMax.QuerySum(1, r - 1) - segTreeMin.QuerySum(1, r - 1);
      }
    }
    return {num, sum};
  }

 public:
  ll maxTotalValue(vector<int>& nums_, const int k) {  //
    nums.swap(nums_);
    n = nums.size();
    if (n == 1) return 0;

    ll maxVal = *max_element(nums.begin(), nums.end());
    ll minVal = *min_element(nums.begin(), nums.end());
    ll maxDis = maxVal - minVal + 1;  // 最大距离

    ll l = 0, r = maxDis;  // [l, r)
    while (l < r) {
      ll mid = (l + r) / 2;
      auto [num, sum] = Search(mid);
      if (num >= k) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    auto [numR, sumR] = Search(r);
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