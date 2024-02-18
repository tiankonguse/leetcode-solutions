// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  bool isPrefixAndSuffix(const string& a, const string& b) {
    int an = a.length();
    int bn = b.length();
    if (an > bn) return false;
    const char* pa = a.data();
    const char* pb = b.data();
    return strncmp(pa, pb, an) == 0 && strncmp(pa, pb + bn - an, an) == 0;
  }

 public:
  int countPrefixSuffixPairs(vector<string>& words) {
    int ans = 0;
    int n = words.size();
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (isPrefixAndSuffix(words[i], words[j])) {
          ans++;
        }
      }
    }
    return ans;
  }
};
