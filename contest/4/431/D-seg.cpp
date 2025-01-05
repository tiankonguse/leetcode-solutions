
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

vector<int> nums;
struct SegTree {
  vector<pair<ll, tuple<int, int, int, int>>> maxVal;  // {w, }

  void Init(int n) {
    maxNM = n;
    maxVal.resize(maxNM << 2);
  }

  const pair<ll, tuple<int, int, int, int>> zero = {0, {INT_MIN, INT_MIN, INT_MIN, INT_MIN}};
  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) { maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]); }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      maxVal[rt] = zero;
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(const int R, const pair<ll, tuple<int, int, int, int>>& add, int l = 1, int r = maxNM, int rt = 1) {
    if (R == nums[l - 1] && nums[r - 1] == R) {
      maxVal[rt] = max(maxVal[rt], add);
      return;
    }
    int m = (l + r) >> 1;
    if (R <= nums[m - 1]) {
      Update(R, add, lson);
    } else {
      Update(R, add, rson);
    }
    PushUp(rt, l, r);
  }
  const pair<ll, tuple<int, int, int, int>>& QueryMax(const int R, int l = 1, int r = maxNM, int rt = 1) {
    if (nums[r - 1] <= R) {
      return maxVal[rt];
    }
    if (l == r) {  // 空洞
      return zero;
    }
    int m = (l + r) >> 1;
    if (R <= nums[m - 1]) {
      return QueryMax(R, lson);
    } else {
      return max(maxVal[rt << 1], QueryMax(R, rson));
    }
  }
};

SegTree segTree;
tuple<int, int, int, int> ToP(const vector<int>& v) {
  int n = v.size();
  if (n == 0) {
    return {INT_MIN, INT_MIN, INT_MIN, INT_MIN};
  } else if (n == 1) {
    return {v[0], INT_MIN, INT_MIN, INT_MIN};
  } else if (n == 2) {
    return {v[0], v[1], INT_MIN, INT_MIN};
  } else if (n == 3) {
    return {v[0], v[1], v[2], INT_MIN};
  } else {
    return {v[0], v[1], v[2], v[3]};
  }
}

vector<int> buf;
vector<int>& ToV(const tuple<int, int, int, int>& t) {
  auto [t0, t1, t2, t3] = t;
  buf.clear();
  buf.push_back(t0);
  buf.push_back(t1);
  buf.push_back(t2);
  buf.push_back(t3);
  while (!buf.empty() && buf.back() == INT_MIN) {
    buf.pop_back();
  }
  return buf;
}

tuple<int, int, int, int> Merge(const tuple<int, int, int, int>& t, int p) {
  vector<int>& buf = ToV(t);
  buf.push_back(p);
  sort(buf.begin(), buf.end(), [](auto a, auto b) { return a > b; });
  return ToP(buf);
}

class Solution {
 public:
  vector<int> maximumWeight(vector<vector<int>>& intervals) {
    int n = intervals.size();
    vector<tuple<int, int, ll, int>> nodes(n);  // <R, L, W, I>

    nums.reserve(n + 1);
    nums.push_back(0);  // 桩，避免 l-1 越界
    for (int i = 0; i < n; i++) {
      nodes[i] = {intervals[i][1], intervals[i][0], intervals[i][2], i};
      nums.push_back(intervals[i][1]);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    sort(nodes.begin(), nodes.end());

    // for (int i = 0; i < int(nums.size()); i++) {
    //   MyPrintf("i=%d v=%d\n", i, nums[i]);
    // }

    segTree.Init(nums.size());
    segTree.Build();

    pair<ll, tuple<int, int, int, int>> ans = {0, {}};

    for (int k = 0; k < 4; k++) {
      for (int i = n - 1; i >= 0; i--) {
        auto [r, l, w, p] = nodes[i];
        auto [W, PS] = segTree.QueryMax(l - 1);  // 找到 小于 l 的最大权重
        pair<ll, tuple<int, int, int, int>> tmp = {W + w, Merge(PS, -p)};
        segTree.Update(r, tmp);
        ans = max(ans, tmp);
      }
    }
    // printf("ans=%lld\n", ans.first);
    vector<int>& buf = ToV(ans.second);
    for (auto& v : buf) {
      v = -v;
    }
    return buf;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<vector<int>> intervals, vector<int> ans) {  //
  TEST_SMP1(Solution, maximumWeight, ans, intervals);
}

int main() {
  // Test({{1, 3, 2}, {4, 5, 2}, {1, 5, 5}, {6, 9, 3}, {6, 7, 1}, {8, 9, 1}}, {2, 3});
  Test({{5, 8, 1}, {6, 7, 7}, {4, 7, 3}, {9, 10, 6}, {7, 8, 2}, {11, 14, 3}, {3, 5, 5}}, {1, 3, 5, 6});
  return 0;
}

#endif