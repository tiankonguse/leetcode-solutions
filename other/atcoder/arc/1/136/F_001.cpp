#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const ll mod = 998244353;
ll modpow(ll a, ll n) {
  ll res = 1;
  while (0 < n) {
    if (n & 1) res = (res * a) % mod;
    a = (a * a) % mod;
    n >>= 1;
  }
  return res;
}
ll A[16];
ll B[16];
ll N, M;
void solve() {
  ll ans = 0;
  vector<ll> b(N + 1);
  b[1] = modpow(A[0], mod - 2);
  for (ll n = 2; n <= N; n++) {
    for (ll k = 1; k < n; k++) {
      b[k] = (b[k] * A[k - 1]) % mod;
      b[k] = (b[k] * modpow((A[k - 1] - A[n - 1] + mod) % mod, mod - 2)) % mod;
      b[n] = (b[n] + mod - b[k]) % mod;
    }
  }

  for (ll bit = 0; bit < (1 << N); bit++) {
    ll sum = 0;
    ll z = 1;
    ll Sum = 0;
    for (ll i = 0; i < N; i++)
      if (bit & (1 << i)) {
        sum++;
        z = (z * modpow(A[i], B[i] + 1)) % mod;
        Sum += (B[i] + 1);
      } else {  
      }
    if (sum & 1) z = (z * (mod - 1)) % mod;

    ll m = M - Sum;
    if (m < 0) continue;
    if (m == 0) {
      ans = (ans + z) % mod;
      continue;
    }

    Sum = 0;
    for (ll i = 1; i <= N; i++) {
      Sum = (Sum + b[i] * modpow(A[i - 1], m + 1)) % mod;
    }
    ans = (ans + z * Sum) % mod;
  }

  cout << ans << endl;
}
int main() {
  cin >> N >> M;
  for (ll i = 0; i < N; i++) cin >> A[i] >> B[i];
  solve();
  return 0;
}