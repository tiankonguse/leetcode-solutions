// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 0;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
const int N = 1000001;
const int M = 78499;
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
  vector<ll> g;

 public:
  int minOperations(vector<int>& nums) {
    int k = getprm();

    ll n = nums.size();
    g.resize(n, -1);
    for (int i = 0; i < n; i++) {
      const ll V = nums[i];
      if (V == 1 || is[V]) {
        continue;
      }
      for (ll j = 0; j < k; j++) {
        if (V % prm[j] == 0) {
          g[i] = prm[j];
          break;
        }
      }
    }
    ll ans = 0;
    for (ll i = n - 2; i >= 0; i--) {
      auto& a = nums[i];
      ll b = nums[i + 1];
      if (a > b) {
        if (g[i] == -1) return -1;  // 没有最小因子
        if (g[i] > b) return -1;    // 最小因子不满足要求
        a = g[i];
        ans++;
      }
    }

    return ans;
  }
};
