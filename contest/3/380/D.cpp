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
ll H(const char* str, int n) {
  ll pre = 0;
  for (int i = 0; i < n; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod1e7;
  }
  return pre;
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
  int Abs(int a, int b) {
    if (a < b) {
      return b - a;
    }
    return a - b;
  }

 public:
  vector<int> beautifulIndices(const string& s, const string& a,
                               const string& b, int k) {
    const int sn = s.length();
    const int an = a.length();
    const int bn = b.length();

    Init(s.data(), s.length());
    const ll ha = H(a.data(), a.length());
    const ll hb = H(b.data(), b.length());

    set<int> h;
    for (int bi = 0; bi + bn <= sn; bi++) {
      if (hb == H(bi, bi + bn - 1)) {
        h.insert(bi);
        // printf("bi=%d\n", bi);
      }
    }

    vector<int> ans;
    ans.reserve(sn);

    if (h.size() == 0) {
      return ans;
    }

    for (int ai = 0; ai + an <= sn; ai++) {
      if (ha != H(ai, ai + an - 1)) {
        continue;
      }
      // printf("ai=%d\n", ai);
      auto it = h.lower_bound(ai);
      if (it != h.end()) {
        int v = *it;
        if (Abs(ai, v) <= k) {
          ans.push_back(ai);
          continue;
        }
      }

      if (it != h.begin()) {
        it--;
        int v = *it;
        if (Abs(ai, v) <= k) {
          ans.push_back(ai);
          continue;
        }
      }
    }

    return ans;
  }
};