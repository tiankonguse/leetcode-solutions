
typedef long long ll;

// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t)
    ;
  return y;
}
ll Lcd(ll x, ll y) { return x * y / Gcd(x, y); }
vector<int> coins; // n 个数字，求第 K 个倍数
int n;

// 原理: a,b,c 两个数字，K 以内的倍数个数为 K/a + K/b + K/c - K/lcd(a,b) - K/lcd(a,c) - K/lcd(b,c) + K/lcd(a,b,c)
// 思路：分为两组，一组与第一个数有关，一组与第一个数无关
// 1) 与第一个数有关 K/a - K/lcd(a,b) - K/lcd(a,c)+ K/lcd(a,b,c)
//   提取 A 后，剩余的数字可以递归 K/a - (K/lcd(a,b) + K/lcd(a,c) - K/lcd(a,b,c))
// 2) 与第一个数无关的，处理逻辑与第一个数类似
// 复杂度：`O(2^n)`
ll rongchi(int index, ll sum, ll pre = 1) {
  if (pre > sum) return 0;
  ll ans = 0;
  for (int i = index; i < n; i++) {
    ll tmp = Lcd(coins[i], pre);
    ans += sum / tmp - rongchi(i + 1, sum, tmp);
  }
  return ans;
}