#include <bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
int a[50010], sum[50010];
int calc(pii x) { return sum[x.fi] - x.se; }
int cnt, st[50010], ed[50010], w[50010], pre[50010], nxt[50010];
void merge(int x, int y) {
  while (st[x] != ed[x] && sum[ed[x]] <= sum[st[y]]) ed[x] = pre[ed[x]];
  if (st[x] == ed[x] && sum[ed[x]] <= sum[st[y]])
    ;
  else
    nxt[ed[x]] = st[y], pre[st[y]] = ed[x], st[y] = st[x];
  st[x] = ed[x] = w[x] = 0;
}
signed main() {
  freopen("query.in", "r", stdin);
  freopen("query.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int n, q;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    sum[i] = sum[i - 1] + a[i];
  }
  cin >> q;
  while (q--) {
    for (int i = 1; i <= cnt; i++) st[i] = ed[i] = w[i] = 0;
    cnt = 0;
    for (int i = 1; i <= n; i++) pre[i] = nxt[i] = 0;
    int l, r;
    cin >> l >> r;
    deque<pii> q1;
    deque<int> q2;
    q2.push_back(++cnt);
    st[cnt] = l, ed[cnt] = l, w[cnt] = 0;
    for (int i = l + 1; i <= r; i++) {
      while (st[cnt] != ed[cnt] && sum[ed[cnt]] <= sum[i]) ed[cnt] = pre[ed[cnt]];
      if (st[cnt] == ed[cnt] && sum[ed[cnt]] <= sum[i])
        st[cnt] = ed[cnt] = i;
      else
        nxt[ed[cnt]] = i, pre[i] = ed[cnt], ed[cnt] = i;
    }
    ull ans = (ull)(!q1.empty() ? calc(q1.front()) : sum[st[q2.front()]] - w[q2.front()]);
    for (int i = 2; i <= n; i++) {
      while (!q2.empty() && st[q2.front()] < i + l - 1) {
        q1.push_back({st[q2.front()], w[q2.front()]});
        if (st[q2.front()] == ed[q2.front()])
          q2.pop_front();
        else
          st[q2.front()] = nxt[st[q2.front()]];
      }
      if (!q1.empty() && q1.front().fi < i) q1.pop_front();
      if (i + r - 1 <= n) {
        q2.push_back(++cnt);
        st[cnt] = ed[cnt] = i + r - 1, w[cnt] = sum[i - 1];
      }
      if (!q2.empty() && w[q2.back()] >= sum[i - 1]) {
        int x = q2.back();
        q2.pop_back();
        while (!q2.empty() && w[q2.back()] >= sum[i - 1]) {
          merge(q2.back(), x);
          q2.pop_back();
        }
        w[x] = sum[i - 1];
        while (!q2.empty() && sum[ed[q2.back()]] - w[q2.back()] <= sum[st[x]] - w[x]) {
          int y = q2.back();
          while (st[y] != ed[y] && sum[ed[y]] - w[y] <= sum[st[x]] - w[x]) ed[y] = pre[ed[y]];
          if (st[y] == ed[y] && sum[ed[y]] - w[y] <= sum[st[x]] - w[x]) q2.pop_back();
        }
        q2.push_back(x);
      }
      while (!q1.empty() && !q2.empty() && calc(q1.back()) <= sum[st[q2.front()]] - w[q2.front()]) q1.pop_back();
      ans ^= (ull)i * (ull)(!q1.empty() ? calc(q1.front()) : sum[st[q2.front()]] - w[q2.front()]);
    }
    cout << ans << '\n';
  }
  return 0;
}
