void floyd(int n, vector<vector<ll>>& g) {
  FOR(k, 0, n) {
    FOR(i, 0, n) {
      if (i == k) continue;
      FOR(j, 0, n) {
        ll tmp = g[i][k] + g[k][j];
        if (tmp < g[i][j]) {
          g[i][j] = tmp;
        }
      }
    }
  }
}