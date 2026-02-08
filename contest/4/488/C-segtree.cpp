
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 758 / 812 个通过的测试用例
// 765 / 812 个通过的测试用例
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
  vector<pair<ll, ll>> minMaxVal;  // 记录最值的位置
  vector<ll> str;

  void Init(vector<int>& str_, const ll default_val = 0) {
    maxNM = str_.size() + 1;
    minMaxVal.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1, default_val);
    for (int i = 0; i < str_.size(); i++) {
      str[i + 1] = str_[i];
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    minMaxVal[rt].first = min(minMaxVal[rt << 1].first,
                                minMaxVal[rt << 1 | 1].first);
    minMaxVal[rt].second = max(minMaxVal[rt << 1].second,
                               minMaxVal[rt << 1 | 1].second);
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      minMaxVal[rt] = {str[l], str[l]};
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  pair<ll, ll> Query(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minMaxVal[rt];
    }
    int m = (l + r) >> 1;
    pair<ll, ll> ret = {__LONG_LONG_MAX__, -1};
    if (L <= m) {
      auto [mimVal, maxVal] = Query(L, R, lson);
      ret.first = min(ret.first, mimVal);
      ret.second = max(ret.second, maxVal);
    }
    if (m < R) {
      auto [mimVal, maxVal] = Query(L, R, rson);
      ret.first = min(ret.first, mimVal);
      ret.second = max(ret.second, maxVal);
    }
    return ret;
  }
};

SegTree segTree;
class Solution {
 public:
  ll countSubarrays(vector<int>& nums, ll k) {
    segTree.Init(nums);
    segTree.Build();
    ll ans = 0;
    int n = nums.size();
    int maxOffset = 1;
    for (int i = 1; i <= n; i++) {
      int l = maxOffset, r = n + 1;
      while (l < r) {
        int m = (l + r) >> 1;
        auto [minVal, maxVal] = segTree.Query(i, m);
        ll cost = (maxVal - minVal) * (m - i + 1);
        if (cost <= k) {
          l = m + 1;
        } else {
          r = m;
        }
      }
      maxOffset = r;
      ans += r - i;
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