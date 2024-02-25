// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool isPossibleToSplit(vector<int>& nums) {
    unordered_map<int, int> h;
    for (auto v : nums) {
      h[v]++;
      if (h[v] > 2) return false;
    }
    return true;
  }
};