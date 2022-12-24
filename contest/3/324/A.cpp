// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int similarPairs(vector<string>& words) {
    unordered_map<int, int> m;
    int ans = 0;
    for (auto& w : words) {
      int bit = 0;
      for (auto v : w) {
        bit = bit | (1 << (v - 'a'));
      }
      ans += m[bit];
      m[bit]++;
    }
    return ans;
  }
};