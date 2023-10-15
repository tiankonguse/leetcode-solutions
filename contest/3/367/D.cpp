// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int mod = 12345;
class Solution {
 public:
  vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid.front().size();

    vector<ll> up(n + 2, 1);
    vector<ll> down(n + 2, 1);
    vector<ll> left(m + 2, 0);
    vector<ll> right(m + 2, 0);

    for (int i = 1; i <= n; i++) {
      ll v = 1;
      for (int j = 1; j <= m; j++) {
        v = (v * grid[i - 1][j - 1]) % mod;
      }
      up[i] = (v * up[i - 1]) % mod;
    }

    for (int i = n; i >= 1; i--) {
      ll v = 1;
      for (int j = 1; j <= m; j++) {
        v = (v * grid[i - 1][j - 1]) % mod;
      }
      down[i] = (v * down[i + 1]) % mod;
    }
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 1; i <= n; i++) {
      ll up_down = (up[i - 1] * down[i + 1]) % mod;

      left.clear();
      left.resize(m + 2, 1);
      right.clear();
      right.resize(m + 2, 1);

      for (int j = 1; j <= m; j++) {
        left[j] = (left[j - 1] * grid[i - 1][j - 1]) % mod;
      }
      for (int j = m; j >= 1; j--) {
        right[j] = (right[j + 1] * grid[i - 1][j - 1]) % mod;
      }

      for (int j = 1; j <= m; j++) {
        ll left_right = (left[j - 1] * right[j + 1]) % mod;
        ans[i - 1][j - 1] = (up_down * left_right) % mod;
      }
    }
    return ans;
  }
};