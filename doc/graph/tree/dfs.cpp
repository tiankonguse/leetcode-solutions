
#include <bits/stdc++.h>
using namespace std;
const int max5 = 5e5 + 5;

vector<int> dfn;  // dfs 序
vector<int> in;   // 进入时间
vector<int> out;  // 离开时间
int t = 0;

void BuildDfn(const int u, const int p) {
  in[u] = t;
  dfn[t] = u;
  t++;
  for (int v : g[u]) {
    if (v == p) continue;
    BuildDfn(v, u);
  }
  out[u] = t;
}
