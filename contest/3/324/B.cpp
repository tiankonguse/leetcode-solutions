// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int N = 200000;
const int M = 20000;
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
  int k;
  int Next(int n) {
    int ans = 0;
    for (int i = 0; i < k && n != 1; i++) {
      while (n % prm[i] == 0) {
        ans += prm[i];
        n /= prm[i];
      }
    }
    return ans;
  }

 public:
  int smallestValue(int n) {
    k = getprm();
    is[4] = 1;
    while (!is[n]) {
      n = Next(n);
    }

    return n;
  }
};
