// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int findTheLongestSubstring(const string& s) {
    const string aeiou = "aeiou";
    vector<int> offset(26, 0);
    for (int i = 0; i < aeiou.size(); i++) {
      offset[aeiou[i] - 'a'] = i + 1;
    }

    unordered_map<int, int> m;
    m[0] = 0;

    int ans = 0;
    int bit = 0;
    for (int i = 1; i <= s.size(); i++) {
      char v = s[i - 1];
      if (offset[v - 'a']) {
        bit ^= (1 << offset[v - 'a']);
      }
      if (m.count(bit)) {
        ans = max(ans, i - m[bit]);
      } else {
        m[bit] = i;
      }
    }
    return ans;
  }
};