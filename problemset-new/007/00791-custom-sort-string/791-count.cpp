#include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
 public:
  string customSortString(const string& order, string ans) {
    vector<int> nums(26, 0);
    for (auto c : ans) {
      nums[c - 'a']++;
    }

    ans.clear();
    for (auto c : order) {
      int i = c - 'a';
      while (nums[i] > 0) {
        ans.push_back(c);
        nums[i]--;
      }
    }
    for (int i = 0; i < nums.size(); i++) {
      while (nums[i] > 0) {
        ans.push_back('a' + i);
        nums[i]--;
      }
    }
    return ans;
  }
};
