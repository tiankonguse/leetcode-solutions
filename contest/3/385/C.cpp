// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int N = 1000000;
const int M = 300000;
bool is[N];
int prm[M];
int K = 0;
int getprm() {
  if (K != 0) return K;
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  memset(is, 1, sizeof(is));
  prm[k++] = 2;
  is[0] = is[1] = 0;
  for (i = 4; i < N; i += 2) is[i] = 0;
  for (i = 3; i < e; i += 2) {
    if (is[i]) {
      prm[k++] = i;
      for (int s = i + i, j = i * i; j < N; j += s) is[j] = 0;
    }
  }
  for (; i < N; i += 2)
    if (is[i]) prm[k++] = i;
  return K = k;
}

int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
class Solution {
 public:
  int mostFrequentPrime(vector<vector<int>>& mat) {
    getprm();

    int n = mat.size();
    int m = mat.front().size();
    unordered_map<int, int> h;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        for (int k = 0; k < 8; k++) {
          int x = i;
          int y = j;
          int v = 0;
          while (x >= 0 && x < n && y >= 0 && y < m) {
            v = v * 10 + mat[x][y];
            if (v > 10 && is[v]) {
              h[v]++;
            }
            x += dir8[k][0];
            y += dir8[k][1];
          }
        }
      }
    }

    int ans = -1;
    int num = 0;

    for (auto [k, v] : h) {
      if (v > num) {
        ans = k;
        num = v;
      } else if (v == num) {
        ans = max(ans, k);
      }
    }

    return ans;
  }
};