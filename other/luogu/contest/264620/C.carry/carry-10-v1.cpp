#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int medule = 998244353;

// 模拟计算 C(l,r)：区间A[l]~A[r]依次累加，统计总进位次数

ll jinwei(const vector<ll>& A, int l, int r) {
  ll S = 0;
  ll cnt = 0;
  for (int i = l; i <= r; i++) {
    ll num = A[i];
    ll t = num;
    ll c = 0;  // 当前这一次加法的进位
    // 从低位到高位，逐位模拟二进制加法，最多40位足够
    for (int j = 0; j <= 40; j++) {
      int x = (S >> j) & 1;
      int y = (t >> j) & 1;
      int total = x + y + c;
      if (total >= 2) {
        c = 1;
        cnt++;  // 产生一次进位，计数+1
      } else {
        c = 0;
      }
    }
    S = S + num;
  }
  return cnt;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<ll> A(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> A[i];
    }
    vector<ll> dp(n + 1, 0);  // dp[i]表示以第i个下标为结尾的合法序列数
    ll ans = 0;

    for (int i = 1; i <= n; i++) {
      dp[i] = 1;  // 单独[i]这个序列，基础是1
      // 枚举所有j < i，判断C(j,i)是否等于1 ,，枚举的子序列
      for (int j = 1; j < i; j++) {
        //优化思路：分析 [1,i-1] 这些下标 jinwei(A, j, i) 的值的特征
        ll c = jinwei(A, j, i);
        if (c == 1) {
          dp[i] = (dp[i] + dp[j]) % medule;
        }
      }
      ans = (ans + dp[i]) % medule;
    }
    cout << ans << endl;
  }
  return 0;
}