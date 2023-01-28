// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool canConstruct(string s, int k) {
    int n = s.length();
    vector<int> nums(26, 0);
    for (auto c : s) {
      nums[c - 'a']++;
    }

    int one = 0;
    for (auto& v : nums) {
      if (v % 2 == 1) {
        one++;
      }
    }

    // 可以构造的个数： [one, n]
    return k >= one && k <= n;
  }
};