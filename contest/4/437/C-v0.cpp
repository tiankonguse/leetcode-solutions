
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
  vector<int> minVal;  // 记录最值的位置

  void Init(int n, const ll default_val = 0) {
    maxNM = n + 1;
    maxVal.resize(maxNM << 2);
    minVal.resize(maxNM << 2);
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      maxVal[rt] = 0;
      minVal[rt] = kMaxVal;
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void UpdateMax(int L, int R, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      maxVal[rt] = add;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) UpdateMax(L, R, add, lson);
    if (R > m) UpdateMax(L, R, add, rson);
    PushUp(rt, l, r);
  }
  void UpdateMin(int L, int R, ll add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      minVal[rt] = add;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) UpdateMin(L, R, add, lson);
    if (R > m) UpdateMin(L, R, add, rson);
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
  ll QueryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    int m = (l + r) >> 1;
    ll ret = 0;
    if (L <= m) {
      ret = min(ret, QueryMin(L, R, lson));
    }
    if (m < R) {
      ret = min(ret, QueryMin(L, R, rson));
    }
    return ret;
  }
};

// 朴素并查集
// 参考资料：https://oi-wiki.org/ds/dsu/
// 树上并查集每个子树需要维护一个集合，保证大集合向小集合合并，并引用返回大集合就不会超时了

class Dsu {
  vector<int> fa;

 public:
  void Init(int n) {
    fa.resize(n);
    for (int i = 0; i < n; i++) {
      fa[i] = i;
    }
  }

  int Find(int x) {
    if (fa[x] != x) {
      fa[x] = Find(fa[x]);
    }
    return fa[x];
  }

  // Union，也成为了 Merge
  void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x != y) {
      if (x > y) {
        fa[y] = x;
      } else {
        fa[x] = y;
      }
    }
  }
};
SegTree segTree0;
SegTree segTree;
Dsu dsu;
class Solution {
  vector<int> dp;

 public:
  bool maxSubstringLength(const string& s, int k) {
    if(k == 0) return true;
    int n = s.size();
    vector<int> firstPos(27, -1);
    vector<int> lastPos(27, -1);
    for (int i = 1; i <= n; i++) {
      int v = s[i - 1] - 'a';
      if (firstPos[v] == -1) {
        firstPos[v] = i;
      }
      lastPos[v] = i;
    }

    dsu.Init(28);
    const int hook = 26;
    firstPos[hook] = 0;
    lastPos[hook] = n + 1;

    for (int i = 0; i < 26; i++) {
      if (firstPos[i] == -1) continue;
      if (i != dsu.Find(i)) continue;  // 被合并了
      int l = firstPos[i];
      int r = lastPos[i];
      // printf("init i=%d v=%c [%d,%d]\n", i, 'a' + i, firstPos[i], lastPos[i]);
    }

    stack<int> sta;
    sta.push(hook);  // 状
    for (int i = 1; i <= n; i++) {
      int v = s[i - 1] - 'a';

      while (1) {
        v = dsu.Find(v);
        int l = firstPos[v];
        int r = lastPos[v];

        int t = dsu.Find(sta.top());  // 可能合并，更新
        if (v == t) break;            // do nothing

        int L = firstPos[t];
        int R = lastPos[t];
        // printf("v=%d c=%c [%d,%d]\n", v, s[i - 1], l, r);
        // printf("top=%d [%d,%d]\n", t, L, R);
        if (l < R && r > R || l < L) {  // 相交，合并
          dsu.Union(t, v);
          l = firstPos[v] = firstPos[t] = min(l, L);
          r = lastPos[v] = lastPos[t] = max(r, R);
          // printf("merge t=%d v=%d [%d,%d]\n", t, v, l, r);
          v = dsu.Find(v);
          sta.pop();
        } else {
          sta.push(v);  // 入栈
          break;
        }
      }

      // 判断栈顶是否是独立区间
      if (lastPos[sta.top()] == i) {
        // printf("find one range v=%d\n", sta.top());
        sta.pop();
      }
    }

    vector<pair<int, int>> nums;
    for (int i = 0; i < 26; i++) {
      if (firstPos[i] == -1) continue;
      if (i != dsu.Find(i)) continue;  // 被合并了
      int l = firstPos[i];
      int r = lastPos[i];
      nums.push_back({l, r});
      // printf("i=%d v=%c [%d,%d]\n", i, 'a' + i, firstPos[i], lastPos[i]);
    }
    if(nums.size() == 1) return false;

    const int nn = n + 2;
    segTree.Init(nn);
    segTree.Build();
    sort(nums.begin(), nums.end(), [](auto& p0, auto& p1) { return p0.first > p1.first; });

    for (auto [l, r] : nums) {
      int nowAns = segTree.QueryMax(l, l);
      int newAns = 1 + segTree.QueryMax(r + 1, nn);
      if (newAns > nowAns) {
        segTree.UpdateMax(l, l, newAns);
      }
    }
    return segTree.QueryMax(1, n) >= k;
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