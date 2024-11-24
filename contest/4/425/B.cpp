
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 29;

ll h[max6];
ll qpowCache[max6];

ll Hash(const char* str, int l, int r) {
  ll pre = 0;
  for (int i = l; i < r; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod1e7;
  }
  return pre;
}

class Solution {
 public:
  bool isPossibleToRearrange(const string& s, const string& t, int k) {
    int n = s.size();
    int nn = n / k;
    vector<ll> sa(k), ta(k);
    for (int i = 0, j = 0; i < n; i += nn, j++) {
      sa[j] = Hash(s.data(), i, i + nn);
      ta[j] = Hash(t.data(), i, i + nn);
    }
    sort(sa.begin(), sa.end());
    sort(ta.begin(), ta.end());
    return sa == ta;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const string& s, const string& t, int k, const bool& ans) {
  TEST_SMP3(Solution, isPossibleToRearrange, ans, s, t, k);
}

int main() {
  Test("abcd", "cdab", 2, true);
  Test("aabbcc", "bbaacc", 3, true);
  Test("aabbcc", "bbaacc", 2, false);
  return 0;
}

#endif