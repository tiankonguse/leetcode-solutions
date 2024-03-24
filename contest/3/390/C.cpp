// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {
    unordered_map<ll, ll> h;
    map<ll, ll> hh;

    vector<ll> ans;
    ans.resize(nums.size());
    for (int i = 0; i < nums.size(); i++) {
      ll val = nums[i];
      ll num = freq[i];

      ll oldFreq = h[val];
      hh[oldFreq]--;
      if (hh[oldFreq] == 0) {
        hh.erase(oldFreq);
      }

      h[val] += num;

      ll newFreq = h[val];
      hh[newFreq]++;

      ans[i] = hh.rbegin()->first;
    }
    return ans;
  }
};