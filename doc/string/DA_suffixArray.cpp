const int maxn = 200010;
int wx[maxn], wy[maxn], *x, *y, wss[maxn], wv[maxn];

bool cmp(int *r, int n, int a, int b, int l) {
  return a + l < n && b + l < n && r[a] == r[b] && r[a + l] == r[b + l];
}
void da(int str[], int sa[], int rank[], int height[], int n, int m) {
  int *s = str;
  int *x = wx, *y = wy, *t, p;
  int i, j;
  for (i = 0; i < m; i++) wss[i] = 0;
  for (i = 0; i < n; i++) wss[x[i] = s[i]]++;
  for (i = 1; i < m; i++) wss[i] += wss[i - 1];
  for (i = n - 1; i >= 0; i--) sa[--wss[x[i]]] = i;
  for (j = 1, p = 1; p < n && j < n; j *= 2, m = p) {
    for (i = n - j, p = 0; i < n; i++) y[p++] = i;
    for (i = 0; i < n; i++)
      if (sa[i] - j >= 0) y[p++] = sa[i] - j;
    for (i = 0; i < n; i++) wv[i] = x[y[i]];
    for (i = 0; i < m; i++) wss[i] = 0;
    for (i = 0; i < n; i++) wss[wv[i]]++;
    for (i = 1; i < m; i++) wss[i] += wss[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--wss[wv[i]]] = y[i];
    for (t = x, x = y, y = t, p = 1, i = 1, x[sa[0]] = 0; i < n; i++)
      x[sa[i]] = cmp(y, n, sa[i - 1], sa[i], j) ? p - 1 : p++;
  }
  for (int i = 0; i < n; i++) rank[sa[i]] = i;
  for (int i = 0, j = 0, k = 0; i < n; height[rank[i++]] = k)
    if (rank[i] > 0)
      for (k ? k-- : 0, j = sa[rank[i] - 1];
           i + k < n && j + k < n && str[i + k] == str[j + k]; k++);
}