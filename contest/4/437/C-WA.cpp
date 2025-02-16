
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

#include <bits/stdc++.h>
/*
线段树：区间修改，区间查询

输入数组： vector<int> str; [0, n-1]

SegTree segTree;
segTree.Init(str); // 内部会对数组进行右移，转化为 [1,n]
segTree.Build();
segTree.Update(l, r, val); // 区间 [l,r] 都加上 val, 数据范围 [1,n]
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
  vector<int> maxVal;  // 记录最值的位置

  void Init(int n, const ll default_val = 0) {
    maxNM = n + 1;
    maxVal.resize(maxNM << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) { maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]); }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      maxVal[rt] = 0;
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, int R, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      maxVal[rt] = add;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
    PushUp(rt, l, r);
  }
  ll QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxVal[rt];
    }
    int m = (l + r) >> 1;
    ll ret = 0;
    if (L <= m) {
      ret = max(ret, QueryMax(L, R, lson));
    }
    if (m < R) {
      ret = max(ret, QueryMax(L, R, rson));
    }
    return ret;
  }
};

SegTree segTree;
class Solution {
  vector<int> dp;

 public:
  bool maxSubstringLength(const string& s, int k) {
    int n = s.size();
    vector<int> firstPos(26, -1);
    vector<int> lastPos(26, -1);
    for (int i = 0; i < n; i++) {
      int v = s[i] - 'a';
      if (firstPos[v] == -1) {
        firstPos[v] = i;
      }
      lastPos[v] = i;
    }
    vector<pair<int, int>> nums;
    for (int i = 0; i < 26; i++) {
      if (firstPos[i] == -1) continue;
      nums.push_back({firstPos[i] + 1, lastPos[i] + 1});
      // printf("i=%d v=%c [%d,%d]\n", i, 'a'+i, firstPos[i] + 1, lastPos[i] + 1);©leetcode
    }

    const int nn = n + 2;
    segTree.Init(nn);
    segTree.Build();
    sort(nums.begin(), nums.end(), [](auto& p0, auto& p1) { return p0.first > p1.first; });
    for (auto [l, r] : nums) {
      int nowAns = segTree.QueryMax(l, l);
      int newAns = 1 + segTree.QueryMax(r + 1, nn);
      // printf("[%d,%d] oldAns=%d newAns=%d\n", l,r, nowAns, newAns);©leetcode
      if (newAns > nowAns) {
        segTree.Update(l, l, newAns);
      }
    }
    return segTree.QueryMax(1, nn) >= k;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif