// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int N = 100000;
const int M = 300000;
bool is[N];
int prm[M];
int K = 0;
int getprm() {
  if(K != 0) return K;
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

class Solution {
 public:
  int nonSpecialCount(int l, int r) {
    getprm();

    ll ans = r - l + 1;
    ll l2 = sqrt(l * 1.0);
    ll r2 = sqrt(r * 1.0);

    for (ll i = l2; i <= r2; i++) {
      ll i2 = i * i;
      if (i2 >= l && i2 <= r && is[i]) {
        ans--;
      }
    }
    return ans;
  }
};