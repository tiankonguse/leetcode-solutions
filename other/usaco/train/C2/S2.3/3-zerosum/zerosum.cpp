/*
ID: tiankonguse
TASK: zerosum
LANG: C++
*/
#define TASK "zerosum"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
int n;
string buf;
vector<string> ans;
string ops = " +-";

void Check() {
  ll pre = 0;
  ll now = 0;
  ll flag = 1;
  buf.push_back('+');
  for (auto c : buf) {
    if (c == '+') {
      pre = pre + flag * now;
      now = 0;
      flag = 1;
    } else if (c == '-') {
      pre = pre + flag * now;
      now = 0;
      flag = -1;
    } else if (c == ' ') {
      // do nothing
    } else {
      now = now * 10 + (c - '0');
    }
  }
  buf.pop_back();
  if (pre == 0) {
    printf("%s\n", buf.c_str());
  }
}

void Dfs(int p) {
  if (p == n + 1) {
    Check();
    return;
  }
  for (auto c : ops) {
    buf.push_back(c);
    buf.push_back('0' + p);
    Dfs(p + 1);
    buf.pop_back();
    buf.pop_back();
  }
}

void Solver() {  //
  scanf("%d", &n);
  buf.reserve(n * 2);
  buf.push_back('1');
  Dfs(2);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
7
1+2-3+4-5-6+7
1+2-3-4+5+6-7
1-2 3+4+5+6+7
1-2 3-4 5+6 7
1-2+3+4-5+6-7
1-2-3-4-5+6+7
*/