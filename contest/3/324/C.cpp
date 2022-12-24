// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  ll M = 100000;
  int n;
  vector<int> odd;
  unordered_set<ll> h;
  ll H(int u, int v) { return u * M + v; }

  bool E(int u, int v) { return h.count(H(u, v)) == 1; }

  bool CheckFour() {
    // 只有三种情况，即第一个点个后面哪三个点结合
    vector<int> boll = {0, 1, 2, 3};
    int i = 0;
    for (int j = 1; j < 4; j++) {
      swap(boll[1], boll[j]);
      int x = boll[2];
      int y = boll[3];

      if (!E(odd[i], odd[j]) && !E(odd[x], odd[y])) {
        return true;
      }

      swap(boll[1], boll[j]);
    }
    return false;
  }

  bool CheckTwo() {
    int x = odd[0], y = odd[1];

    // 第一种情况：可以直接加一条边
    if (!E(x, y)) {
      return true;
    }

    // 第二种情况，存在第三者来牵线,这时候需要加两条边
    for (int i = 0; i < n; i++) {
      if (i == x || i == y) continue;
      if (E(i, x) || E(i, y)) continue;
      return true;
    }

    return false;
  }

 public:
  bool isPossible(int n, vector<vector<int>>& edges) {
    this->n = n;
    vector<int> deg(n);
    for (auto& e : edges) {
      int u = e[0] - 1, v = e[1] - 1;
      deg[u]++;
      deg[v]++;
      h.insert(H(u, v));
      h.insert(H(v, u));
    }

    for (int i = 0; i < deg.size(); i++) {
      if (deg[i] % 2 == 1) {
        odd.push_back(i);
        if (odd.size() > 4) return false;
      }
    }

    if (odd.size() == 0) {
      return true;
    }

    if (odd.size() == 4) {
      return CheckFour();
    } else {
      return CheckTwo();
    }
  }
};
