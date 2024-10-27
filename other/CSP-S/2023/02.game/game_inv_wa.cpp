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
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
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
const int NN = 1000;
const int MM = 100;
bool is[NN];
int prm[MM];
int getprm() {
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  memset(is, 1, sizeof(is));
  prm[k++] = 2;
  is[0] = is[1] = 0;
  for (i = 4; i < NN; i += 2) is[i] = 0;
  for (i = 3; i < e; i += 2) {
    if (is[i]) {
      prm[k++] = i;
      for (int s = i + i, j = i * i; j < NN; j += s) is[j] = 0;
    }
  }
  for (; i < NN; i += 2)
    if (is[i]) prm[k++] = i;
  return k;
}

/*

*/

void Solver() {
  vector<ll> X7(26);
  vector<ll> X9(26);
  vector<ll> RX7(26);
  vector<ll> RX9(26);

  int K = getprm();
  for (int i = 0; i < 26; i++) {
    K--;
    X7[i] = prm[K];
    RX7[i] = inv(X7[i], mod1e7);
    // printf("i=%d X7=%lld RX7=%lld *=%lld\n", i, X7[i], RX7[i],
    //        (X7[i] * RX7[i]) % mod1e7);

    K--;
    X9[i] = prm[K];
    RX9[i] = inv(X9[i], mod1e9);
    // printf("i=%d X9=%lld RX9=%lld *=%lld\n", i, X9[i], RX9[i],
    //        (X9[i] * RX9[i]) % mod1e9);
  }

  ll n;
  scanf("%lld%s", &n, str);
  unordered_map<ll, ll> h;

  stack<char> sta;
  ll pre7 = 1;
  ll pre9 = 1;
  ll ans = 0;
  h[pre7 * mod1e9 + pre9] = 1;
  for (int i = 0; i < n; i++) {
    const char c = str[i];
    const ll v = c - 'a';

    if (i & 1) {
      pre7 = (pre7 * X7[v]) % mod1e7;
      pre9 = (pre9 * X9[v]) % mod1e9;
    } else {
      pre7 = (pre7 * RX7[v]) % mod1e7;
      pre9 = (pre9 * RX9[v]) % mod1e9;
    }
    // printf("i=%d add+%lld\n", i, h[pre]);
    ll pre = pre7 * mod1e9 + pre9;
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