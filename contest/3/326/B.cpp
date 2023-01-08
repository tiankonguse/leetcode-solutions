// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int N = 2000;
const int M = 2000;
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
  int distinctPrimeFactors(vector<int>& nums) {
    int k = getprm();
    unordered_set<int> h;
    for (auto v : nums) {
      for (int i = 0; i < k && v > 1; i++) {
        while (v % prm[i] == 0) {
          v /= prm[i];
          h.insert(prm[i]);
        }
      }
    }
    return h.size();
  }
};