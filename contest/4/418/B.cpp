// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
  vector<int> flag;
  vector<vector<int>> g;
  vector<vector<int>> rg;
  const int KEYI = 1;
  const int UP = 2;
  const int DOWN = 4;

 public:
  vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
    flag.resize(n, 0);
    g.resize(n);
    rg.resize(n);
    for (auto& v : invocations) {
      g[v[0]].push_back(v[1]);
      rg[v[1]].push_back(v[0]);
    }
    queue<int> keYi;
    keYi.push(k);
    flag[k] |= KEYI;
    while (!keYi.empty()) {
      int a = keYi.front();
      keYi.pop();
      for (int b : g[a]) {
        if ((flag[b] & KEYI) != KEYI) {
          flag[b] |= KEYI;
          keYi.push(b);
        }
      }
    }

    queue<int> up;
    queue<int> down;

    for (int i = 0; i < n; i++) {
      if ((flag[i] & KEYI) == 0) {
        up.push(i);
        flag[i] |= UP;
        down.push(i);
        flag[i] |= DOWN;
      }
    }

    auto Solver = [&](int b) {
      int& p = flag[b];
      if (p & KEYI) {
        p ^= KEYI;
      }
      if ((flag[b] & UP) == 0) {
        p |= UP;
        up.push(b);
      }
      if ((flag[b] & DOWN) == 0) {
        down.push(b);
        p |= DOWN;
      }
    };

    while (!up.empty() || !down.empty()) {
      if (!down.empty()) {
        int a = down.front();
        down.pop();
        for (int b : g[a]) {
          Solver(b);
        }
      }
      if (!up.empty()) {
        int a = up.front();
        up.pop();
        for (int b : rg[a]) {
          Solver(b);
        }
      }
    }

    vector<int> ans;
    ans.reserve(n);
    for (int i = 0; i < n; i++) {
      if ((flag[i] & KEYI) == 0) {
        ans.push_back(i);
      }
    }
    return ans;
  }
};