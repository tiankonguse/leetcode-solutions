// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int findPermutationDifference(const string& s, const string& t) {
    unordered_map<char, int> h;
    for (int i = 0; i < s.length(); i++) {
      h[s[i]] = i;
    }

    int ans = 0;
    for (int i = 0; i < t.length(); i++) {
      ans += abs(h[t[i]] - i);
    }
    return ans;
  }
};