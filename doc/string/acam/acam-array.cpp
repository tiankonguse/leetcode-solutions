#include <bits/stdc++.h>
using namespace std;

// 参考 https://www.luogu.com.cn/record/246126191

const int N = 200010, L = 5000010, C = 27;
const char _ = 'z' + 1;
int n, m, tree[L][C], cnt, ed[L], fail[L], st[L];

void add(string& s) {
  int p = 0;
  for (char c : s) {
    int x = c - 'a';
    if (!tree[p][x]) tree[p][x] = ++cnt;
    p = tree[p][x];
  }
  ++ed[p];
}

void build() {
  queue<int> q;
  for (int j = 0; j < C; ++j)
    if (tree[0][j]) q.emplace(tree[0][j]);
  while (q.size()) {
    int p = q.front();
    q.pop();
    for (int j = 0; j < C; ++j)
      if (!tree[p][j])
        tree[p][j] = tree[fail[p]][j];
      else
        fail[tree[p][j]] = tree[fail[p]][j], q.emplace(tree[p][j]);
  }
}

int ask(string& s, int id) {
  int res = 0, p = 0;
  for (char c : s) {
    p = tree[p][c - 'a'];
    for (int j = p; j && st[j] != id; j = fail[j]) {
      res += ed[j];
      st[j] = id;
    }
  }
  return res;
}