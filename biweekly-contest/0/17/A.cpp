// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> decompressRLElist(vector<int>& nums) {
    int len = 0;
    int n = nums.size();
    for (int i = 0; i < n; i += 2) {
      len += nums[i];
    }

    vector<int> ans;
    ans.reserve(len);
    for (int i = 0; i < n; i += 2) {
      int freq = nums[i];
      int v = nums[i + 1];
      while (freq--) {
        ans.push_back(v);
      }
    }
    return ans;
  }
};