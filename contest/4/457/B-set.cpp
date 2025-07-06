
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
class Dsu {
  vector<int> fa;
  vector<int> rank;

 public:
  void Init(int n) {
    fa.resize(n);
    rank.resize(n);
    for (int i = 0; i < n; i++) {
      fa[i] = i;
      rank[i] = 1;
    }
  }
  int Find(int p) {
    if (fa[p] != p) {
      fa[p] = Find(fa[p]);
    }
    return fa[p];
  }
  int Union(int u, int v) {
    u = Find(u);
    v = Find(v);
    if (u == v) return u;
    if (rank[u] > rank[v]) {
      swap(u, v);
    }
    rank[v] += rank[u];
    fa[u] = v;
    return v;
  }
};
Dsu dsu;
class Solution {
 public:
  vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
    dsu.Init(c + 1);
    for (auto& connection : connections) {
      int u = connection[0];
      int v = connection[1];
      dsu.Union(u, v);
    }
    unordered_map<int, set<int>> H;
    for (int i = 1; i <= c; i++) {
      int p = dsu.Find(i);
      H[p].insert(i);
    }
    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      int t = q[0], x = q[1];
      int p = dsu.Find(x);
      auto& HP = H[p];
      if (t == 1) {
        if (HP.empty()) {
          ans.push_back(-1);
        } else if (HP.count(x)) {
          ans.push_back(x);
        } else {
          ans.push_back(*HP.begin());
        }
      } else {
        HP.erase(x);
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