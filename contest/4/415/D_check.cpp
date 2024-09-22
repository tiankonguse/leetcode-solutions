// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 29;
const ll BASE7 = 29;
const ll BASE9 = 29;

class Solution {
  unordered_map<ll, tuple<ll, int, int> > h;
  int n;
  int MAXANS;

 public:
  int minValidStrings(vector<string>& words, const string& target) {
    n = target.size();
    MAXANS = n + 1;
    // h.resize(n + 1);

    for (int k = 0; k < words.size(); k++) {
      auto& word = words[k];
      ll pre7 = 0;
      ll pre9 = 0;
      for (int i = 0; i < word.size() && i < n; i++) {
        const char v = word[i];
        pre7 = (pre7 * BASE7 + (v - 'a' + 1)) % mod1e7;
        pre9 = (pre9 * BASE7 + (v - 'a' + 1)) % mod1e9;
        if (h.count(pre7)) {
          auto [p7, pk, pi] = h[pre7];
          if (p7 != pre9) {
            myprintf("hash one pre7[%lld], double pre9[%lld,%lld] [%s, %s] \n",
                     pre7, pre9, p7, words[k].substr(0, i + 1).c_str(),
                     words[pk].substr(0, pi + 1).c_str());
          }
        } else {
          h[pre7] = {pre9, k, i};
        }
      }
    }
    for (int i = 0; i < n; i++) {
      ll pre7 = 0;
      ll pre9 = 0;
      for (int j = i; j < n; j++) {
        const char v = target[j];
        pre7 = (pre7 * BASE7 + (v - 'a' + 1)) % mod1e7;
        pre9 = (pre9 * BASE7 + (v - 'a' + 1)) % mod1e9;
        if (h.count(pre7)) {
          auto [p7, pk, pi] = h[pre7];
          if (p7 != pre9) {
            myprintf("hash one pre7[%lld], double pre9[%lld,%lld] [%s, %s] \n",
                     pre7, pre9, p7, target.substr(i, j - i + 1).c_str(),
                     words[pk].substr(0, pi + 1).c_str());
          }
        } else {
          // h[pre7] = pre9;
        }
      }
    }
    return 0;
  }
};