// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  int numberOfSubstrings(const string& s, int k) {
    ll ans = 0;
    ll n = s.size();
    vector<ll> stat;
    for (int i = 0; i < n; i++) {
      stat.clear();
      stat.resize(26, 0);
      for (int j = i; j < n; j++) {
        int v = s[j] - 'a';
        stat[v]++;
        if (stat[v] >= k) {
          ans += n - j;
          break;
        }
      }
    }
    return ans;
  }
};