// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 29;

ll h[max3];
ll qpowCache[max3];

ll H(int l, int r) {
  if (l == 0) return h[r];
  ll pre = h[l - 1] * qpowCache[r - l + 1] % mod1e7;
  return (h[r] - pre + mod1e7) % mod1e7;
}

void Init(const char* str, int n) {
  qpowCache[0] = 1;
  for (int i = 1; i <= n; i++) {
    qpowCache[i] = (qpowCache[i - 1] * BASE) % mod1e7;
  }

  ll pre = 0;
  for (int i = 0; i < n; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod1e7;
    h[i] = pre;
  }
}
class Solution {
 public:
  int distinctEchoSubstrings(const string& text) {
    int n = text.size();
    Init(text.c_str(), n);

    unordered_set<ll> hs;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j += 2) {
        int len = j - i + 1;
        ll lh = H(i, i + len / 2 - 1);
        ll rh = H(i + len / 2, j);
        if (lh == rh) {
          hs.insert(lh);
        }
      }
    }
    return hs.size();
  }
};