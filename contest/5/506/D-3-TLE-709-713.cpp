
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 超出时间限制 709 / 713 个通过的测试用例
int debug = 0;
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
  vector<pair<ll, int>> vals;  // 记录值的位置
  vector<ll> sumVal;
  vector<ll> countVal;

  void Init(int n) {
    maxNM = n + 1;
    vals.resize(maxNM << 2);
    sumVal.resize(maxNM << 2);
    countVal.resize(maxNM << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
    countVal[rt] = countVal[rt << 1] + countVal[rt << 1 | 1];
  }
  int Num(pair<ll, ll> p) { return p.second - p.first + 1; }
  void Reset(int rt, int l) {
    vals[rt] = {0, l};
    sumVal[rt] = 0;
    countVal[rt] = 0;
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      Reset(rt, l);
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Set(int L, ll val, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      vals[rt].first = val;
      sumVal[rt] = val;
      countVal[rt] = 1;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Set(L, val, lson);
    if (L > m) Set(L, val, rson);
    PushUp(rt, l, r);
  }
  void Unset(int L, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      Reset(rt, l);
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Unset(L, lson);
    if (L > m) Unset(L, rson);
    PushUp(rt, l, r);
  }

  // 返回有值的第 k 个元素与位置
  pair<ll, int> Rank(int k, int l = 1, int r = maxNM, int rt = 1) {
    assert(countVal[rt] >= k);
    if (l == r) {
      return vals[rt];
    }
    int m = (l + r) >> 1;
    if (countVal[rt << 1] >= k) {
      return Rank(k, lson);
    } else {
      return Rank(k - countVal[rt << 1], rson);
    }
  }
  ll Count() {  //
    return countVal[1];
  }
  ll QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L > R) return 0;
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

SegTree segTreeWindows;
SegTree segTreeOther;
class Solution {
  // 返回最大子数组和
  ll MaxSumArray(vector<int>& nums) {
    ll maxSum = nums[0], curSum = 0;
    for (ll x : nums) {
      curSum = max(x, curSum + x);
      maxSum = max(maxSum, curSum);
    }
    return maxSum;
  }

 public:
  ll maxSum(vector<int>& nums, const int K) {  //
    if (K == 0) {
      return MaxSumArray(nums);
    }
    int n = nums.size();
    // 第一步：基于离散化
    vector<pair<ll, ll>> sortedNums;
    sortedNums.reserve(n);
    for (int i = 1; i <= n; i++) {
      sortedNums.push_back({nums[i - 1], i});
    }
    sort(sortedNums.begin(), sortedNums.end());
   vector<int> rank(n+1);
    for (int i = 1; i <= n; i++) {
      rank[sortedNums[i - 1].second] = i;
    }
    ll ans = nums.front();
    // len = 1, 等于最大值
    ans = max(ans, sortedNums.rbegin()->first);
    // len = n, 等于 sum(nums)
    ans = max(ans, accumulate(nums.begin(), nums.end(), 0LL));

    for (int len = 2; len < n; len++) {
      const int windowsSize = len;
      const int otherSize = n - len;
      segTreeWindows.Init(n);
      segTreeOther.Init(n);
      segTreeWindows.Build();
      segTreeOther.Build();

      ll sumWindow = 0, sumOther = 0;
      for (int i = 1; i <= n; i++) {
        const int val = nums[i - 1];
        const pair<ll, ll> node = {val, i};
        const int idx = rank[i];
        segTreeOther.Set(idx, val);
        sumOther += val;
      }
      for (int i = 1; i <= n; i++) {
        // i 加入 window, 从 other 中删除
        const int right = i, left = i - len;  // (left, right]
        const ll rightVal = nums[right - 1];
        const pair<ll, ll> rightNode = {rightVal, right};
        const int idxRight = rank[right];

        segTreeWindows.Set(idxRight, rightVal);
        sumWindow += rightVal;

        segTreeOther.Unset(idxRight);
        sumOther -= rightVal;

        if (left < 0) continue;
        if (left >= 1) {
          // i - len - 1 从 window 中删除，加入 other
          const int leftVal = nums[left - 1];
          const pair<ll, ll> leftNode = {leftVal, left};
          const int idxLeft = rank[left];

          segTreeWindows.Unset(idxLeft);
          sumWindow -= leftVal;

          segTreeOther.Set(idxLeft, leftVal);
          sumOther += leftVal;
        }
        MyPrintf("-------\n");
        MyPrintf("len = %d, (%d, %d], sumWindow = %lld, sumOther = %lld\n", len, left, right, sumWindow, sumOther);

        // 窗口最小值 不小于 其他最大值，不需要交换
        if (segTreeWindows.Rank(1).first >= segTreeOther.Rank(otherSize).first) {
          MyPrintf("不需要交换, ans = %lld\n", sumWindow);
          ans = max(ans, sumWindow);
          continue;
        }

        int l = 1, r = min(min(windowsSize, otherSize), K) + 1;  // [l, r)
        MyPrintf("l = %d, r = %d, windowsSize=%d otherSize=%d K=%d\n", l, r, windowsSize, otherSize, K);
        assert(r <= windowsSize + 1);
        assert(r <= otherSize + 1);
        while (l < r) {
          int mid = (l + r) >> 1;
          // window 的前 mid 个元素 都不大于 other 的后 mid 个元素
          MyPrintf("segTreeWindows count=%d val=%d\n", segTreeWindows.Count(), mid);
          MyPrintf("segTreeOther count=%d val=%d\n", segTreeOther.Count(), otherSize - mid + 1);
          if (segTreeWindows.Rank(mid).first <= segTreeOther.Rank(otherSize - mid + 1).first) {
            l = mid + 1;
          } else {
            r = mid;  // 不满足
          }
        }
        MyPrintf("l = %d, r = %d\n", l, r);
        r--;
        auto [val, idx] = segTreeWindows.Rank(r);
        MyPrintf("windowsSize=%d r=%d val = %lld, idx = %d\n", windowsSize, r, val, idx);
        auto [val2, idx2] = segTreeOther.Rank(otherSize - r + 1);
        MyPrintf("otherSize=%d r=%d val2 = %lld, idx2 = %d\n", otherSize, otherSize - r + 1, val2, idx2);

        ll sum = segTreeWindows.QuerySum(idx + 1, n) + segTreeOther.QuerySum(idx2, n);
        MyPrintf("len = %d, (%d, %d], r=%d sum = %lld\n", len, left, right, r, sum);
        ans = max(ans, sum);
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