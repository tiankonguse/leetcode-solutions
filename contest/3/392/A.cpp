// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int Solver(vector<int>& nums) {
    int pre = nums.front();
    int num = 0;
    int ans = 1;
    for (auto v : nums) {
      if(v > pre){
        pre = v;
        num++;
      }else{
        pre = v;
        num = 1;
      }
      ans = max(ans,num);
    }
    return ans;
  }

 public:
  int longestMonotonicSubarray(vector<int>& nums) {
    int ans = 1;
    ans = max(ans, Solver(nums));
    std::reverse(nums.begin(), nums.end());
    ans = max(ans, Solver(nums));
    return ans;
  }
};