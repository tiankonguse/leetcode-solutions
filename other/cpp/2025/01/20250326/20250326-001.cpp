/*
【题目描述】 给你一根长度为n的绳子，请把绳子剪成m段
(m和n都是整数，n>=1并且m>1)每段绳子的长度记为k[0],k[1],…,k[m].请问k[0]k[1]…*k[m]可能的最大乘积是多少？ 【输入】
绳子的长度n(2=<n<=60)
【输出】
最大的乘积
【样例输入】
8
【样例输出】
18


*/

#include <bits/stdc++.h>
typedef long long ll;
class Solution {
 public:
  vector<ll> dp;  // 任意拆分的最大乘积

 public:
  ll maxProduct(int n) {
    if (n == 1) return 0;
    dp.resize(n + 1, -1);
    ll ans = 1;
    // 枚举第一段的长度
    for (ll i = 1; i < n; i++) {
      ans = max(ans, i * dfs(n - i));
    }
    return ans;
  }

  ll dfs(int n) {
    if (dp[n] != -1) return dp[n];
    if (n == 1) return dp[n] = 1;

    ll maxVal = n;
    // 尝试在不同位置切割
    for (ll i = 1; i < n; i++) {
      maxVal = max(maxVal, i * dfs(n - i));
    }

    return dp[n] = maxVal;
  }
};

int main() {
  Solution s;
  for (int i = 1; i <= 60; i++) {
    cout << i << " " << s.maxProduct(i) << endl;
  }
  return 0;
}