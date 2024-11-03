#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n;
ll L, R;
int a[200005];
int b[200005];
int c[200005];
vector<int> ans;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>
    q;

ll check(int x) {
  int pos = n;
  ll cnt = 0;
  for (int i = 1; i <= n; i++) {
    while (pos > 0 && a[i] + b[pos] > x) pos--;
    cnt += pos;
  }
  return cnt;
}

int main() {
  scanf("%d%lld%lld", &n, &L, &R);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &b[i]);
  }
  sort(a + 1, a + n + 1);
  sort(b + 1, b + n + 1);
  int l = 0, r = 2e9;
  while (l <= r) {
    int m = ((ll)l + r) / 2;
    if (check(m) < L)
      l = m + 1;
    else
      r = m - 1;
  }
  for (int i = 0; i < min(check(l) - L + 1, R - L + 1); i++) {
    ans.push_back(l);
  }
  int pos = n;
  for (int i = 1; i <= n; i++) {
    while (pos > 0 && a[i] + b[pos] > l) pos--;
    c[i] = pos + 1;
    if (c[i] <= n) q.push({a[i] + b[c[i]], i});
  }
  while (ans.size() < R - L + 1) {
    auto p = q.top();
    q.pop();
    ans.push_back(p.first);
    c[p.second]++;
    if (c[p.second] <= n) q.push({a[p.second] + b[c[p.second]], p.second});
  }
  for (int i = 0; i < ans.size(); i++) {
    printf("%d%c", ans[i], i < (int)ans.size() - 1 ? ' ' : '\n');
  }
  return 0;
}