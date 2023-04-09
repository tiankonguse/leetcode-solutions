// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int N = 5000000;
const int M = 400000;
bool is[N];
int prm[M];
int getprm() {
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
  return k;
}

class Solution {
 public:
  int diagonalPrime(vector<vector<int>>& nums) {
    int k =getprm();
      // printf("k=%d\n", k);
    int ans = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      int v = nums[i][i];
      if (is[v]) {
        ans = max(ans, v);
      }
      v = nums[i][n - i - 1];

      if (is[v]) {
        ans = max(ans, v);
      }
    }
    return ans;
  }
};