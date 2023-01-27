// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> sortByBits(vector<int>& arr) {
    vector<pair<int, int>> nums;
    for (auto v : arr) {
      nums.push_back({__builtin_popcount(v), v});
    }
    sort(nums.begin(), nums.end());
    arr.clear();
    for (auto [one, v] : nums) {
      arr.push_back(v);
    }
    return arr;
  }
};