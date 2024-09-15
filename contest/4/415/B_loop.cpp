// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll NINFL = -INFL;
constexpr ll one = 1;
typedef long long ll;

class Solution {
 public:
  long long maxScore(vector<int>& a, vector<int>& b) {
    int n = a.size();
    int m = b.size();
    vector<ll> f(5, NINFL);
    f[0] = 0;
    for (int i = 1; i <= m; i++) {
      for (int j = min(n, i); j >= 1; j--) {
        f[j] = max(f[j], f[j - 1] + one * b[i - 1] * a[j - 1]);
      }
    }

    return f[4];
  }
};