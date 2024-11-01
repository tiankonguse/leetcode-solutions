#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e5 + 10;
int a[maxn], b[maxn], n;
ll L, R, Ln, Rn, Lm, Rm;
vector<int> ans;
bool judge(int x, ll f) {
  ll r = 0;
  int p = 0;
  for (int i = n - 1; i >= 0; i--) {
    while (a[i] + b[p] <= x && p < n) ++p;
    r += p;
  }
  if (f <= r) return 1;
  return 0;
}
ll solve(ll f) {
  ll l = a[0] + b[0], r = a[n - 1] + b[n - 1], mid;
  ll num = -1;
  while (l <= r) {
    mid = (l + r) / 2;
    if (judge(mid, f)) {
      num = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return num;
}
int main() {
  cin >> n >> L >> R;
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) cin >> b[i];
  sort(a, a + n);
  sort(b, b + n);
  Ln = solve(L);
  Rn = solve(R);
  if (Ln == Rn) {
    for (int i = 0; i <= (R - L); ++i) {
      cout << Ln << " ";
    }
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    int p = upper_bound(b, b + n, Ln - a[i]) - b;
    for (int j = p; j < n; ++j) {
      if (a[i] + b[j] >= Rn) break;
      ans.push_back(a[i] + b[j]);
    }
  }
  ll tmp = 0;
  for (int i = 0; i < n; ++i) tmp += upper_bound(b, b + n, Ln - a[i]) - b;
  Lm = tmp - L + 1;
  Rm = R - L + 1 - Lm - ans.size();
  for (int i = 0; i < Lm; ++i) cout << Ln << ' ';
  sort(ans.begin(), ans.end());
  for (int i : ans) cout << i << ' ';
  for (int i = 0; i < Rm; ++i) cout << Rn << ' ';
  return 0;
}