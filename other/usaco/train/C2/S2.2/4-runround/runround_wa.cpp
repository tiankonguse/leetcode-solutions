/*
ID: tiankonguse
TASK: runround
LANG: C++
*/
#define TASK "runround"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

char str[20];
int n;
vector<int> flag(10, 0);
string buf;

bool Dfs(const int p, bool minVal) {
  if (p == n) return true;
  int v = str[p] - '0';
  int start = v;
  if (minVal) {  // 从最小值找答案
    v = 0;
    start = 1;
  }
//   printf("p=%d minVal=%d v=%d start=%d\n", p, minVal, v, start);

  for (int i = start; i < 10; i++) {
    if (i == 0) continue;   // 不能是 0
    if (flag[i]) continue;  // 已经使用了
    flag[i] = 1;
    buf[p] = '0' + i;
    if (Dfs(p + 1, i != v)) {
      return true;
    }
    flag[i] = 0;
  }
  return false;
}

void Solver() {  //
  scanf("%s", str + 1);
  str[0] = '0';
  n = strlen(str);
  buf = str;

  // 检查是否需要进位，进位后答案是 123456
  if (!Dfs(1, false)) {
    for (int i = 0; i < n; i++) {
      buf[i] = '0' + i + 1;
    }
    printf("%s\n", buf.data());
    return;
  }

  printf("%s\n", buf.data() + 1);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
81362
13628136
281362
81
3
628


99
100
123
2
31



*/