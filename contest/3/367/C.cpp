// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> findIndices(vector<int>& nums, int indexDifference,
                          int valueDifference) {
    int n = nums.size();
    // if (indexDifference == 0) {
    //   if (valueDifference == 0) {
    //     return {0, 0};
    //   } else {
    //     return {-1, -1};
    //   }
    // }

    map<ll, unordered_set<int>> h;
    int l = 0, r = indexDifference;  //[l, r)
    h[nums[l]].insert(l);
    l++;

    while (r < n) {
      ll v = nums[r];
      ll minV = v - valueDifference;
      ll maxV = v + valueDifference;

      auto itMax = h.lower_bound(maxV);
      if (itMax != h.end()) {
        int i = *itMax->second.begin();
        return {i, r};
      }

      auto itMin = h.upper_bound(minV);
      if (itMin != h.begin()) {
        itMin--;
        int i = *itMin->second.begin();
        return {i, r};
      }

     if(l < n){
      h[nums[l]].insert(l);
      l++;
     }
      r++;
    }
    return {-1, -1};
  }
};