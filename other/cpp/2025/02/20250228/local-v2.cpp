// 求 C(n,m) % MOD ,MOD=1e9+7, N=1e5, 需要预处理，然后 O(1) 提供任意查询

#include <iostream>
#include <vector>
using namespace std;
const int MOD = 1000000007;
int C[1005][1005];
void init() {
  for (int i = 0; i <= 1000; i++) {
    C[i][0] = 1;
  }
  for (int i = 1; i <= 1000; i++) {
    for (int j = 1; j <= i; j++) {
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
  }
}
int main() {
  init();
  int n, m;
  while (cin >> n >> m) {
    cout << C[n][m] << endl;
  }
  return 0;
}
/*
 * 输入描述:
 * 第一行两个整数 N, MOD，表示预处理的最大值和模数。
 * 接下来有多组测试用例，每组包含两个整数 n, m，表示要求 C(n,m) % MOD 的结果。
 * 输出描述:
 * 对于每组测试用例，输出一行，包含一个整数，表示 C(n,m) % MOD 的值。
 * 示例1
 * 输入
 * 复制
 * 4 3
 * 2 3
 * 5 2
 * 输出
 * 复制
 * 6
 * 0
 */
