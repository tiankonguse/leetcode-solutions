
typedef long long ll;
// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t)
    ;
  return y;
}
class Solution {
  vector<int> flag;
  vector<int> next;

  int Loop(int p) {
    int ans = 0;
    while (flag[p] == 0) {
      flag[p] = 1;
      ans++;
      p = next[p];
    }
    return ans;
  }

 public:
  int reinitializePermutation(int n) {
    next.resize(n, 0);
    for (int i = 0; i < n; i++) {
      if (i % 2 == 0) {
        next[i] = i / 2;
      } else {
        next[i] = n / 2 + (i - 1) / 2;
      }
    //   printf("%d->%d\n", i, next[i]);
    }


    int ans = 1;
    flag.resize(n, 0);
    for (int i = 0; i < n; i++) {
      if (flag[i]) continue;
      int k = Loop(i);
    //   printf("i=%d k=%d ans=%d\n", i, k, ans);
      ans = k / gcd(ans, k) * ans;
    }
    return ans;
  }
};