
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

// 朴素并查集
// 参考资料：https://oi-wiki.org/ds/dsu/
// 树上并查集每个子树需要维护一个集合，保证大集合向小集合合并，并引用返回大集合就不会超时了

class Dsu {
  vector<int> fa, score;

 public:
  void Init(int n) {
    fa.resize(n);
    score.resize(n);
    for (int i = 0; i < n; i++) {
      fa[i] = i, score[i] = 0;
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
      if (score[x] > score[y]) {
        fa[y] = x;
      } else {
        fa[x] = y;
        if (score[x] == score[y]) {
          ++score[y];
        }
      }
    }
  }
  void AddScore(int x) {
    x = Find(x);
    score[x]++;
  }

  int GetScore(int x) {
    x = Find(x);
    return score[x];
  }
};
Dsu dsu;
class Solution {
 public:
  int maxActivated(vector<vector<int>>& points) {
    int n = points.size();
    dsu.Init(n);
    unordered_map<int, int> groupX, groupY;
    for (int i = 0; i < n; i++) {
      auto& point = points[i];
      int x = point[0], y = point[1];
      if (groupX.count(x)) {
        int j = groupX[x];
        dsu.Union(i, j);
      } else {
        groupX[x] = i;
      }
      if (groupY.count(y)) {
        int j = groupY[y];
        dsu.Union(i, j);
      } else {
        groupY[y] = i;
      }
    }
    unordered_map<int, int> cnt;
    for (int i = 0; i < n; i++) {
      int root = dsu.Find(i);
      cnt[root]++;
    }
    if (cnt.size() == 1) {
      return n + 1;  // 额外加一个点
    }
    vector<ll> exCnt;
    exCnt.reserve(cnt.size());
    for (auto& [_, c] : cnt) {
      exCnt.push_back(c);
    }
    // 逆序排序
    sort(exCnt.rbegin(), exCnt.rend());
    return exCnt[0] + exCnt[1] + 1;  // 额外加一个点
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