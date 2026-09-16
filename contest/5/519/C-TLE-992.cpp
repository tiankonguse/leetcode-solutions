
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

// 988 / 999 个通过的测试用例

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
  vector<pair<ll, int>> minVal;  // 记录最值的位置
  vector<pair<ll, int>> maxVal;  // 记录最值的位置
  vector<ll> sumVal;
  vector<pair<ll, ll>> ranges;
  vector<ll> str;

  void Init(int n, const ll default_val = 0) {
    maxNM = n + 1;
    minVal.resize(maxNM << 2);
    maxVal.resize(maxNM << 2);
    sumVal.resize(maxNM << 2);
    ranges.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1, default_val);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
  }
  int Num(pair<ll, ll> p) { return p.second - p.first + 1; }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    ranges[rt] = {l, r};
    if (l == r) {
      sumVal[rt] = str[l];  // 如果 str 没有复制一份，则需要注意边界是否越界
      minVal[rt] = maxVal[rt] = {str[l], l};
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Add(int L, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      minVal[rt].first += add;
      maxVal[rt].first += add;
      sumVal[rt] += add * Num(ranges[rt]);
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Add(L, add, lson);
    if (L > m) Add(L, add, rson);
    PushUp(rt, l, r);
  }
  void Set(int L, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      minVal[rt].first = add;
      maxVal[rt].first = add;
      sumVal[rt] = add;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Set(L, add, lson);
    if (L > m) Set(L, add, rson);
    PushUp(rt, l, r);
  }
  pair<ll, int> QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxVal[rt];
    }
    int m = (l + r) >> 1;
    pair<ll, int> ret = {-1, 0};
    if (L <= m) {
      ret = max(ret, QueryMax(L, R, lson));
    }
    if (m < R) {
      ret = max(ret, QueryMax(L, R, rson));
    }
    return ret;
  }
  pair<ll, int> QueryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    int m = (l + r) >> 1;
    pair<ll, int> ret = {__LONG_LONG_MAX__, 0};  // 求最小值，初始值设置为最大值
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
  // 离散化，值映射到 [1,n]
  void Init(vector<int>& nums) {
    map<int, int> mp;
    for (auto v : nums) {
      mp[v] = 0;
    }
    int offset = 1;
    for (auto& [v, index] : mp) {
      index = offset++;
    }
    for (auto& v : nums) {
      v = mp[v];
    }
  }

 public:
  ll shadowPairs(vector<int>& nums) {
    Init(nums);
    int n = nums.size();
    segTree.Init(n + 1, kMaxVal);
    segTree.Build();
    vector<tuple<ll, ll, ll>> tasks;
    tasks.reserve(n * 2);

    auto Find = [&](const int i, const int v) {
      MyPrintf("Find: i = %d, v = %d\n", i, v);
      // 求位置 i 右侧第一个小于 v 的位置
      pair<ll, int> minVal = segTree.QueryMin(1, n + 1);
      int r = n + 1;
      if (minVal.first >= v) {
        MyPrintf("no find minval: minVal: %lld, v: %d, right use r=%d\n", minVal.first, v, r);
      } else {
        // 存在小于 v 的位置
        int l = 1;
        r = minVal.second;
        while (l < r) {
          int m = (l + r) >> 1;
          if (segTree.QueryMin(1, m).first < v) {
            r = m;
          } else {
            l = m + 1;
          }
        }
        MyPrintf("find minval: minVal: %lld, v: %d, right use r=%d\n", minVal.first, v, r);
      }
      if (i + 1 == r) {
        MyPrintf("no ans, i + 1 == r, skip\n");
        return;
      }
      pair<ll, int> maxVal = segTree.QueryMax(i + 1, r - 1);
      if (maxVal.first <= v) {
        MyPrintf("no ans,no maxVal = %lld, skip\n", maxVal.first);
        return;
      }

      MyPrintf("Add task: pos=%d v = %d, flag = %d\n", r - 1, v + 1, 1);
      MyPrintf("Add task: pos=%d v = %d, flag = %d\n", i - 1, v + 1, -1);
      tasks.push_back({r - 1, v + 1, 1});   // 加上 [1, r) 的值都大于 v 的个数
      tasks.push_back({i - 1, v + 1, -1});  // 减去 [1, i) 的值都大于 v 的个数
    };

    for (int i = n; i > 0; i--) {
      int v = nums[i - 1];
      Find(i, v);
      // 更新位置 i 的值
      segTree.Set(i, v);
    }

    sort(tasks.begin(), tasks.end());
    segTree.Init(n + 1, 0);
    segTree.Build();
    ll ans = 0;
    int maxTask = tasks.size();
    int taskIdx = 0;
    while (taskIdx < maxTask && get<0>(tasks[taskIdx]) == 0) {
      taskIdx++;  // skip 0
    }
    for (int i = 1; i <= n; i++) {
      segTree.Add(nums[i - 1], 1);
      while (taskIdx < maxTask && get<0>(tasks[taskIdx]) == i) {
        const auto [_, v, flag] = tasks[taskIdx];
        ll num = segTree.QuerySum(v, n + 1);
        MyPrintf("Add ans:i=%d v = %lld, num = %lld, flag = %lld\n", i, v, num, flag);
        ans += num * flag;
        taskIdx++;
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