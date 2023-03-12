// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int vowelStrings(vector<string>& words, int left, int right) {
    int ans = 0;
    set<char> s = {'a', 'e', 'i', 'o', 'u'};
    for (int i = left; i <= right; i++) {
      string& w = words[i];
      if (s.count(w.front()) && s.count(w.back())) {
        ans++;
      }
    }
    return ans;
  }
};