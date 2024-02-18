// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 29;

ll h[max6];
ll qpowCache[max6];

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
  long long countPrefixSuffixPairs(vector<string>& words) {
    ll ans = 0;
    unordered_map<ll, ll> h;

    for (const auto& s : words) {
      const int n = s.size();
      Init(s.data(), n);
      for (int i = 1; i <= n; i++) {
        ll pre = H(0, i - 1);
        ll suf = H(n - i, n - 1);
        // printf("pre=%s,%lld suf=%s,%lld\n", s.substr(0, i).c_str(), pre,
        //        s.substr(n - i).c_str(), suf);
        if (pre == suf && h.count(pre)) {
          ans += h[pre];
        }
      }
      h[H(0, n - 1)]++;
    }

    return ans;
  }
};