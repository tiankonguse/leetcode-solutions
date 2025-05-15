
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
      fa[i] = i, score[i] = 1;
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
        score[x] += score[y];
      } else {
        fa[x] = y;
        score[y] += score[x];
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
class Solution {
 public:
  ll maxScore(int n, vector<vector<int>>& edges) {
Dsu dsu;
dsu.Init(n);
unordered_set<int> loop;
for (auto& edge : edges) {
  int u = dsu.Find(edge[0]);
  int v = dsu.Find(edge[1]);
  if (u == v) {
    loop.insert(u);
  } else {
    dsu.Union(u, v);
  }
}
vector<ll> links;
vector<ll> loops;
for (int i = 0; i < n; i++) {
  int f = dsu.Find(i);
  if (i == f) {
    if (loop.count(f)) {
      loops.push_back(dsu.GetScore(f));
    } else {
      links.push_back(dsu.GetScore(f));
    }
  }
}
sort(links.begin(), links.end(), greater<ll>());
sort(loops.begin(), loops.end(), greater<ll>());
ll ans = 0;
ll index = n;
enum { LINK = 0, LOOP = 1 };
auto Next = [&](int v, int type) {
  ll l = index--;
  ll r = l;
  v--;
  while (v >= 2) {
    ll L = index--;
    ll R = index--;
    ans += l * L;
    ans += r * R;
    l = L;
    r = R;
    v -= 2;
  }
  if (v == 1) {
    ll L = index--;
    ll R = L;
    ans += l * L;
    if (type == LOOP) {
      ans += r * R;
    }
  } else {
    if (type == LOOP) {
      ans += l * r;
    }
  }
};
for (ll v : loops) {  // 长度为 v 的环
  Next(v, LOOP);
}
for (ll v : links) {  // 长度为 v 的链
  Next(v, LINK);
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