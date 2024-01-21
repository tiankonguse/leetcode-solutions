// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

typedef long long ll;
class Solution {
 public:
  int minimumPushes(const string& word) {
    vector<int> nums(26, 0);
    for (auto c : word) {
      nums[c - 'a']++;
    }
    sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });

    int index = 2;
    int lev = 1;
    int ans = 0;
    for (auto v : nums) {
      ans += lev * v;
      index++;
      if (index == 10) {
        index = 2;
        lev++;
      }
    }
    return ans;
  }
};