// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
    vector<bool> ans;
    int maxVal = *max_element(candies.begin(), candies.end());
    for (auto v : candies) {
      ans.push_back(v + extraCandies >= maxVal);
    }
    return ans;
  }
};