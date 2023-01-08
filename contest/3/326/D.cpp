// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int N = 1010000;
const int M = 101000;
bool is[N];
int prm[M];
int k = -1;
int getprm() {
  if (k != -1) return k;
  k = 0;

  int e = (int)(sqrt(0.0 + N) + 1), i;
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
  vector<int> closestPrimes(int left, int right) {
    getprm();

    int l = lower_bound(prm, prm + k, left) - prm;
    if (prm[l + 1] > right) {
      return {-1, -1};
    }
    int a = prm[l], b = prm[l + 1];
    while (prm[l + 1] <= right) {
      int x = prm[l], y = prm[l + 1];
      if (y - x < b - a) {
        a = x;
        b = y;
      }
      l++;
    }
    return {a, b};
  }
};