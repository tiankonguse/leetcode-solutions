// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int N = 11000;
const int M = 1435;
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

class Solution {
 public:
  long long maximumSum(vector<int>& nums) {
    getprm();

    printf("K=%d\n", K);

    ll ans = 0;
    unordered_map<ll, ll> m;
    int n = nums.size();
    for (int i = 1; i <= n; i++) {
      ll v = i;
      ll leftBit = 1;
      for (int k = 0; k < K && v > 1; k++) {
        int count = 0;
        while (v % prm[k] == 0) {
          count++;
          v /= prm[k];
        }
        if (count % 2 == 1) {
          leftBit *= prm[k];
        }
      }
      m[leftBit] += nums[i-1];
      ans = max(ans, m[leftBit]);
    }

    return ans;
  }
};