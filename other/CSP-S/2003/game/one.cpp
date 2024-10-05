#include <bits/stdc++.h>
using namespace std;
#define int long long
int rd() {
  int x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + (ch - '0');
    ch = getchar();
  }
  return x * w;
}

void wt(int x) {
  static int sta[35];
  int f = 1;
  if (x < 0) f = -1, x *= f;
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  if (f == -1) putchar('-');
  while (top) putchar(sta[--top] + 48);
}
const int N = 2e6 + 5;
int n;
char s[N];
int dp[N];
int to[N]; // 向前，第一个不匹配的坐标
int f[N][26]; // 当前列，匹配的循环节里面，出现的最后一个单词的位置
int ans;

signed main() {
  scanf("%lld", &n);
  scanf("%s", s + 1);
  for (int i = 1; i <= n; i++) {
    to[i] = i;
    int x;
    x = f[to[i - 1]][s[i] - 'a'];
    printf("i=%d to[i-1]=%d x=%d\n", i, to[i - 1], x);
    if (x) {
      to[i] = to[x - 1], dp[i] = dp[x - 1] + 1;
      printf("to[i]=to[x - 1]=%d\n", to[x - 1]);
    }
    f[to[i]][s[i] - 'a'] = i;
    printf("to[i]=%d f[to[i]]=%d\n", to[i], i);
    printf("i=%d ans=%d\n", i, dp[i]);
    ans += dp[i];
  }
  wt(ans);
  return 0;
}

/*
8
abbccdda
*/