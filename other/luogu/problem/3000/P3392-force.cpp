#include <bits/stdc++.h>
using namespace std;
const int N = 55;
char str[N][N];  // 每一行的颜色字符串
typedef long long ll;
int n, m;

ll fill_num(int a, int b, const char c) {
  ll num = 0;
  for (int i = a; i <= b; i++) {
    for (int j = 0; j < m; j++) {
      if (str[i][j] != c) {
        num++;
      }
    }
  }
  return num;
}

int main() {
  scanf("%d%d", &n, &m);
  ll min_num = n * m;
  for (int i = 0; i < n; i++) {
    scanf("%s", str[i]);
  }

  // [0, i] [i+1,j] [j+1, n-1]
  for (int i = 0; i < n - 2; i++) {
    for (int j = i + 1; j < n - 1; j++) {
      ll w = fill_num(0, i, 'W');
      ll b = fill_num(i + 1, j, 'B');
      ll r = fill_num(j + 1, n - 1, 'R');
      min_num = min(min_num, w + b + r);
    }
  }
  printf("%lld\n", min_num);
  return 0;
}