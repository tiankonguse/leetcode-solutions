
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
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
struct SegTree {
  vector<ll> sumVal;
  vector<ll> countVal;

  void Init(int n, const ll default_val = 0) {
    maxNM = n + 1;
    sumVal.resize(maxNM << 2);
    countVal.resize(maxNM << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
    countVal[rt] = countVal[rt << 1] + countVal[rt << 1 | 1];
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      sumVal[rt] = 0;
      countVal[rt] = 0;
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void UpdateSet(int L, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L == 0) assert(0);
    if (L == l && r == L) {
      sumVal[rt] = add;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) UpdateSet(L, add, lson);
    if (L > m) UpdateSet(L, add, rson);
    PushUp(rt, l, r);
  }
  void UpdateTop(int L, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L == 0) assert(0);
    if (L == l && r == L) {
      countVal[rt] = add;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) UpdateTop(L, add, lson);
    if (L > m) UpdateTop(L, add, rson);
    PushUp(rt, l, r);
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
  ll QueryTop(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return countVal[rt];
    }
    int m = (l + r) >> 1;
    ll ret = 0;
    if (L <= m) {
      ret += QueryTop(L, R, lson);
    }
    if (m < R) {
      ret += QueryTop(L, R, rson);
    }
    return ret;
  }
};

SegTree segTree;
class Solution {
  ll F(ll l, ll r) {
    ll n = r - l + 1;
    return (1 + n) * n / 2;
  }

 public:
  vector<ll> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {  //
    int n = nums.size();
    segTree.Init(n + 1);
    segTree.Build();

    set<int> P;

    auto Get = [&](int i) -> ll { return nums[i - 1]; };
    auto Set = [&](int i, int val) { nums[i - 1] = val; };

    auto Update = [&](int i) {
      if (i <= 1 || i >= n) return;  // 不可能是峰值
      segTree.UpdateSet(i, 0);       // 先清空
      segTree.UpdateTop(i, 0);
      P.erase(i);
      if (Get(i) > Get(i - 1) && Get(i) > Get(i + 1)) {
        P.insert(i);
        segTree.UpdateTop(i, 1);
        auto it = P.lower_bound(i);
        if (it != P.begin()) {
          auto prev = it;
          prev--;
          segTree.UpdateSet(i, F(*prev, *it));
        }
        auto next = it;
        next++;
        if (next != P.end()) {
          segTree.UpdateSet(*next, F(*it, *next));
        }
      } else {
        auto next = P.lower_bound(i);
        if (next != P.end() && next != P.begin()) {
          auto prev = next;
          prev--;
          segTree.UpdateSet(*next, F(*prev, *next));
        }
      }
    };

    for (int i = 1; i <= n; i++) {
      Update(i);
    }

    auto Query = [&](ll l, ll r) -> ll {
      if (l + 1 >= r) return 0;  // 需要至少 3 个点
      auto itLeft = P.upper_bound(l);
      if (itLeft == P.end() || *itLeft >= r) return 0;
      // 此时，保证一定至少有一个峰值在 (l,r) 之间
      ll p1 = *itLeft;
      auto itRight = P.lower_bound(r);
      itRight--;
      ll p2 = *itRight;

      if (p1 == p2) {  // 只有一个峰值
        ll p = p1;
        return (p - l) * (r - p);
      }
      ll all = F(l, r);  // 所有子数组个数
      ll leftPart = F(l, p1);
      ll rightPart = F(p2, r);
      ll midPart = segTree.QuerySum(p1 + 1, p2);
      ll m = segTree.QueryTop(p1, p2);  // 分割点分别多计算一次

      return all - leftPart - rightPart - midPart + m;
    };

    vector<ll> ans;
    ans.reserve(queries.size());
    for (auto& qs : queries) {
      int op = qs[0];
      if (op == 1) {
        const int l = qs[1] + 1;
        const int r = qs[2] + 1;
        ans.push_back(Query(l, r));
      } else {
        const int index = qs[1] + 1;
        const int val = qs[2];
        Set(index, val);
        // 修改 index，影响 index-1, index, index+1
        Update(index - 1);
        Update(index);
        Update(index + 1);
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& nums, const vector<vector<int>>& queries, const vector<ll>& ans) {
  TEST_SMP2(Solution, countOfPeaks, ans, nums, queries);
}

int main() {
  /*
[7,15,0,11,5]
[[2,1,9],[1,0,4]]
  */
  vector<int> nums = {7, 15, 0, 11, 5};
  // vector<vector<int>> queries = {{1, 0, 4}, {2, 1, 9}, {1, 0, 4}};
  vector<vector<int>> queries = {{1, 0, 4}};
  vector<ll> ans = {5};
  Test(nums, queries, ans);
  return 0;
}

#endif