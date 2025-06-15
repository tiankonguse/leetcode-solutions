/*
ID: tiankonguse
TASK: game
LANG: C++
CONTEST: CSP-S 2023
OJ: https://qoj.ac/problem/7814
*/
#define TASK "game"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const ll BASE = 29;

const int N = 2000010;
const int M = 26;
char str[N];
void InitIO() {
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "4"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

ll qpow(ll x, ll v, ll mod) {
  x = x % mod;
  ll y = 1;
  while (v) {
    if (v & 1) y = y * x % mod;
    x = x * x % mod;
    v >>= 1;
  }
  return y;
}
ll inv(ll x, ll mod) { return qpow(x, mod - 2, mod); }

/*

*/

void Solver() {
  ll n;
  scanf("%lld%s", &n, str);
  unordered_map<ll, ll> h;
  stack<char> sta;
  ll pre7 = 0;
  ll pre9 = 0;
  ll ans = 0;
  h[0] = 1;
  for (int i = 0; i < n; i++) {
    const char c = str[i];
    const ll v = c - 'a' + 1;
    if (!sta.empty() && sta.top() == c) {
      int k = sta.size();
      sta.pop();
      pre7 = ((pre7 - v * qpow(BASE, k, mod1e7)) % mod1e7 + mod1e7) % mod1e7;
      pre9 = ((pre9 - v * qpow(BASE, k, mod1e9)) % mod1e9 + mod1e9) % mod1e9;
    } else {
      sta.push(c);
      int k = sta.size();
      pre7 = (pre7 + v * qpow(BASE, k, mod1e7)) % mod1e7;
      pre9 = (pre9 + v * qpow(BASE, k, mod1e9)) % mod1e9;
    }
    // printf("i=%d add+%lld\n", i, h[pre]);
    ll pre = pre9;
    ans += h[pre];
    h[pre]++;
  }

  printf("%lld\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
8
accabccb

*/