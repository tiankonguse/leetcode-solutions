// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  vector<int> getSneakyNumbers(vector<int>& nums) {
    vector<int> ans;
    sort(nums.begin(), nums.end());
    int pre = -1;
    for (auto v : nums) {
      if (v == pre) {
        ans.push_back(v);
      }
      pre = v;
    }
    return ans;
  }
};