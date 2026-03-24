  int PackZeroOne(vector<int>& w, int W) {
    int n = w.size();
    vector<int> f(W + 1, 0);
    // C++ Version
    for (int i = 0; i < n; i++) {
      for (int l = W; l >= w[i]; l--) {
        f[l] = max(f[l], f[l - w[i]] + w[i]);
      }
    }
    return f[W];
  }