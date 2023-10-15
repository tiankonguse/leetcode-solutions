// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> findIndices(vector<int>& nums, int indexDifference,
                          int valueDifference) {
    int n = nums.size();
    int minPos = 0, maxMos = 0;
    int l = 0, r = indexDifference;  //[l, r)
    l++;

    while (r < n) {
      ll v = nums[r];

      if (abs(v - nums[minPos]) >= valueDifference) {
        return {r, minPos};
      }

      if (abs(v - nums[maxMos]) >= valueDifference) {
        return {r, maxMos};
      }

      if (l < n) {
        if(nums[l] < nums[minPos]){
          minPos = l;
        }
        if(nums[l] > nums[maxMos]){
          maxMos = l;
        }
        l++;
      }
      r++;
    }
    return {-1, -1};
  }
};