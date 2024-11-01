#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod1 = 1e9 + 7;
const ll mod2 = 1e9 + 9;
const int base = 131;
int n;
char s[100005];
ll h1[2][100005];
ll h2[2][100005];
ll b1[100005];
ll b2[100005];
ll a[100005];
int c[100005][26];
ll d1[100005];
ll d2[100005];
ll ans = 0;

pair<ll, ll> _hash1(int l, int r) {
  ll _h1 = (h1[0][r] - h1[0][l - 1] * b1[r - l + 1]) % mod1;
  _h1 = (_h1 + mod1) % mod1;
  ll _h2 = (h2[0][r] - h2[0][l - 1] * b2[r - l + 1]) % mod2;
  _h2 = (_h2 + mod2) % mod2;
  return {_h1, _h2};
}
pair<ll, ll> _hash2(int l, int r) {
  ll _h1 = (h1[1][l] - h1[1][r + 1] * b1[r - l + 1]) % mod1;
  _h1 = (_h1 + mod1) % mod1;
  ll _h2 = (h2[1][l] - h2[1][r + 1] * b2[r - l + 1]) % mod2;
  _h2 = (_h2 + mod2) % mod2;
  return {_h1, _h2};
}

inline bool check1(int l, int r) {
  ll _h0 = (h1[0][r] - h1[0][l - 1] * b1[r - l + 1]) % mod1;
  _h0 = (_h0 + mod1) % mod1;
  ll _h1 = (h1[1][l] - h1[1][r + 1] * b1[r - l + 1]) % mod1;
  _h1 = (_h1 + mod1) % mod1;
  return _h0 == _h1;
}
inline bool check2(int l, int r) {
  ll _h0 = (h2[0][r] - h2[0][l - 1] * b2[r - l + 1]) % mod2;
  _h0 = (_h0 + mod2) % mod2;
  ll _h1 = (h2[1][l] - h2[1][r + 1] * b2[r - l + 1]) % mod2;
  _h1 = (_h1 + mod2) % mod2;
  return _h0 == _h1;
}
inline bool check(int l, int r) { return check1(l, r) && check2(l, r); }
void calc() {
  b1[0] = 1;
  b2[0] = 1;
  for (int i = 1; i <= 100000; i++) {
    b1[i] = b1[i - 1] * base % mod1;
    b2[i] = b2[i - 1] * base % mod2;
  }
  for (int i = 1; i <= n; i++) {
    h1[0][i] = (h1[0][i - 1] * base + s[i]) % mod1;
    h2[0][i] = (h2[0][i - 1] * base + s[i]) % mod2;
  }
  for (int i = n; i >= 1; i--) {
    h1[1][i] = (h1[1][i + 1] * base + s[i]) % mod1;
    h2[1][i] = (h2[1][i + 1] * base + s[i]) % mod2;
  }
}

int judge1(int i) {
  int l = 0, r = min(i - 1, n - i);
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(i - m, i + m))
      l = m + 1;
    else
      r = m - 1;
  }
  return r;
}
int judge2(int i) {
  if (s[i] != s[i + 1]) return -1;
  int l = 0, r = min(i - 1, n - i - 1);
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(i - m, i + m + 1))
      l = m + 1;
    else
      r = m - 1;
  }
  return r;
}
int judge3(int L, int R) {
  if (L <= 0 || R > n) return 0;
  int l = 1, r = min(L, n - R + 1);
  while (l <= r) {
    int m = (l + r) / 2;
    if (_hash1(L - m + 1, L) == _hash2(R, R + m - 1))
      l = m + 1;
    else
      r = m - 1;
  }
  return r;
}

int main() {
  // freopen("palinilap2.in","r",stdin);
  scanf("%s", s + 1);
  n = strlen(s + 1);
  calc();
  for (int i = 1; i <= n; i++) {
    int x = judge1(i);
    ans += x + 1;
    int L = i - x, R = i + x;

    // Todo
    for (int j = L; j < i; j++) a[j] += j - L + 1;
    for (int j = R; j > i; j--) a[j] += R - j + 1;
    if (L > 1 && R < n) {
      int y = judge3(L - 2, R + 2);
      c[L - 1][s[R + 1] - 'a'] += y + 1;
      c[R + 1][s[L - 1] - 'a'] += y + 1;
    }
  }
  for (int i = 1; i < n; i++) {
    int x = judge2(i);
    ans += x + 1;
    int L = i - x, R = i + x + 1;

    // Todo
    for (int j = L; j <= i; j++) a[j] += j - L + 1;
    for (int j = R; j > i; j--) a[j] += R - j + 1;

    if (L > 1 && R < n) {
      int y = judge3(L - 2, R + 2);
      c[L - 1][s[R + 1] - 'a'] += y + 1;
      c[R + 1][s[L - 1] - 'a'] += y + 1;
    }
  }
  ll ma = 0;
  for (int i = 1; i <= n; i++) {
    int x = 0;
    for (int j = 0; j < 26; j++) x = max(x, c[i][j]);
    ma = max(ma, x - a[i]);
  }
  cout << ans + ma << endl;
  return 0;
}