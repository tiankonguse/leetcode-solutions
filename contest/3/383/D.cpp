// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 29;

ll h[max5];
ll qpowCache[max5];

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
  int minimumTimeToInitialState(const string& word, int k) {
    int n = word.length();
    Init(word.data(), n);
    const char* p = word.data();
    for (int i = 1; i * k < n; i++) {
      int offset = i * k;
      int len = n - offset;
      if (H(0, len - 1) == H(offset, offset + len - 1)) {
        return i;
      }
    }
    return (n + k - 1) / k;
  }
};