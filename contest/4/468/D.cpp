
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
  vector<ll> str;

  void Init(vector<int>& str_, const ll default_val = 0) {
    maxNM = str_.size() + 1;
    minVal.resize(maxNM << 2);
    maxVal.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1, default_val);
    for (int i = 0; i < str_.size(); i++) {
      str[i + 1] = str_[i];
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      minVal[rt] = maxVal[rt] = str[l];
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  ll QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxVal[rt];
    }
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
};

SegTree segTree;
class Solution {
  ll n;
  vector<int> nums;
  vector<pair<ll, int>> orderedNums;
  vector<ll> leftLast, rightLast;  // 区间内 [leftLast[i], rightLast[i]] , 位置 i 的值最小
  vector<ll> leftMax, rightMax;
  void Init() {
    n = nums.size();

    segTree.Init(nums);
    segTree.Build();

    vector<int> sta;

    sta.reserve(n);
    leftLast.resize(n + 1);
    leftMax.resize(n + 1);
    for (int i = 1; i <= n; i++) {  // 从左到右, 单调递增栈，等于时按左边的小于右边的
      while (!sta.empty() && nums[sta.back() - 1] > nums[i - 1]) {
        sta.pop_back();
      }
      if (sta.empty()) {  // 当前是最小值
        leftLast[i] = 1;
      } else {
        leftLast[i] = sta.back() + 1;
      }
      sta.push_back(i);
      leftMax[i] = segTree.QueryMax(leftLast[i], i);
    }

    rightLast.resize(n + 1);
    rightMax.resize(n + 1);
    sta.clear();
    for (int i = n; i >= 1; i--) {  // 从右到左, 单调递增栈，等于时按左边的小于右边的
      while (!sta.empty() && nums[sta.back() - 1] >= nums[i - 1]) {
        sta.pop_back();
      }
      if (sta.empty()) {  // 当前是最小值
        rightLast[i] = n;
      } else {
        rightLast[i] = sta.back() - 1;
      }
      sta.push_back(i);
      rightMax[i] = segTree.QueryMax(i, rightLast[i]);
    }

    for (int i = 1; i <= n; i++) {
      orderedNums.push_back({nums[i - 1], i});
    }
    sort(orderedNums.begin(), orderedNums.end());
  }

  ll Check(const ll d, const ll minNum) {  // 大于等于d 的个数
    // 定义：对于一个区间，最小值存在多个时，选择最左边的。
    if (d == 0) {
      return n * (n + 1) / 2;
    }

    ll num = 0;
    for (const auto [minVal, i] : orderedNums) {  // 从小到大枚举所有位置
      ll leftFirst = leftLast[i];                 // 默认都可以随意选择
      if (leftMax[i] - minVal >= d) {             // 左边存在答案
        int L = leftLast[i], R = i;               // 找到区间内 [l, r) 最后一个满足大于等于 minVal+d 的位置
        while (L < R) {
          int mid = (L + R) / 2;
          if (segTree.QueryMax(mid, i) - minVal < d) {
            R = mid;
          } else {
            L = mid + 1;
          }
        }
        leftFirst = R;       // 如果左边存在答案，则更新找到第一个位置
        const ll p = R - 1;  // [R-1, i] 是最小的答案
        num += (p - leftLast[i] + 1) * (rightLast[i] - i + 1);
        if (num > minNum) {
          return num;
        }
      }

      if (rightMax[i] - minVal >= d) {  // 右边存在答案
        int L = i, R = rightLast[i];    // 找到区间内 [l, r) 第一个满足大于等于 minVal+d 的位置
        while (L < R) {
          int mid = (L + R) / 2;
          if (segTree.QueryMax(i, mid) - minVal < d) {
            L = mid + 1;
          } else {
            R = mid;
          }
        }
        const ll p = L;  // [i, L] 是最小的答案
        num += (i - leftFirst + 1) * (rightLast[i] - p + 1);
        if (num > minNum) {
          return num;
        }
      }
    }
    return num;
  }

 public:
  ll maxTotalValue(vector<int>& nums_, const int k) {  //
    nums.swap(nums_);

    Init();

    vector<pair<ll, ll>> topK;
    topK.reserve(k + 1);
    ll maxVal = *max_element(nums.begin(), nums.end());
    ll minVal = *min_element(nums.begin(), nums.end());
    topK.push_back({maxVal - minVal + 1, 0});

    // 二分找到小于 topK.back() 的最大值以及个数
    ll sum = 0;
    while (sum < k) {                       //
      const ll preVal = topK.back().first;  // 当前大于等于 preVal 的区间有 sum 个
      ll r = preVal, l = 0;                 // [l, r)
      // ll leftNum = n * (n - 1) / 2;
      while (l < r) {
        ll mid = (l + r) / 2;
        if (Check(mid, sum) > sum) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      ll nowVal = l - 1;
      ll nowNum = Check(nowVal, __LONG_LONG_MAX__);
      topK.push_back({nowVal, nowNum - sum});
      sum = nowNum;
    }

    ll ans = 0;
    sum = 0;
    for (auto [val, num] : topK) {
      MyPrintf("val=%lld, num=%lld sum=%lld\n", val, num, sum);
      if (sum + num <= k) {
        ans += val * num;
        sum += num;
      } else {
        ans += val * (k - sum);
        sum = k;
        break;
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