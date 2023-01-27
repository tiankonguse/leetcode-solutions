// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string sortString(string s) {
    vector<int> nums(26, 0);
    int leftNum = s.size();
    for (char c : s) {
      nums[c - 'a']++;
    }

    s.clear();
    while (leftNum > 0) {
      // up
      for (int i = 0; i < 26; i++) {
        if (nums[i]) {
          s.push_back('a' + i);
          nums[i]--;
          leftNum--;
        }
      }

      // down
      for (int i = 25; i >= 0; i--) {
        if (nums[i]) {
          s.push_back('a' + i);
          nums[i]--;
          leftNum--;
        }
      }
    }
    return s;
  }
};
