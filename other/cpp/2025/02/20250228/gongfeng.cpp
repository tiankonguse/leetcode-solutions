// 求 C(n,m) % MOD ,MOD=1e9+7, N=1e5, 需要预处理，然后 O(1) 提供任意查询

#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e5 + 10;
int C[N][N];

int main() {
  int n, m;
  cin >> n >> m;
  C[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
  }
  cout << C[n][m] << endl;
  return 0;
}
