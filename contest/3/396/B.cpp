// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
const ll BASE = 29;
class Solution {
 public:
  int minimumOperationsToMakeKPeriodic(const string& word, int k) {
    unordered_map<ll, int> h;
    int n = word.length();
    auto Hash = [&word](int l, int r) -> ll {
      ll pre = 0;
      for (int i = l; i < r; i++) {
        pre = (pre * BASE + (word[i] - 'a' + 1)) % mod1e7;
      }
      return pre;
    };
    for (int i = 0; i < n; i += k) {
      h[Hash(i, i + k)]++;
    }

    int ans = 1;
    for (auto [k, v] : h) {
      ans = max(ans, v);
    }
    return n / k - ans;
  }
};
