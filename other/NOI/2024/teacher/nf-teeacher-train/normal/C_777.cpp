#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
const int MAXN = 11;
const int MAXK = 1e5 + 10;
long long f[MAXN][MAXK], s[MAXN][MAXK], n, k;
/*
A<=B  A~K
若A>B 则B不是能是A的因子 1~A-1中的非因子
*/
int main() {
  cin >> n >> k;
  for (int i = 1; i <= k; ++i) {
    f[1][i] = 1;
    s[1][i] += s[1][i - 1] + f[1][i];
  }
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j <= k; ++j) {
      f[i][j] = (f[i][j] + s[i - 1][k]) % MOD;
      int tk = 2;
      while (tk * j <= k) {
        f[i][j] = (f[i][j] - f[i - 1][tk * j] + MOD) % MOD;
        tk++;
      }
      s[i][j] = (s[i][j - 1] + f[i][j]) % MOD;
    }
  }
  cout << s[n][k];
  return 0;
}