// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int findSmallestInteger(vector<int>& nums, int k) {
    vector<int> mods(k, 0);
    for (auto v : nums) {
      mods[(v % k + k) % k]++;
    }

    int ans = 0;
    int index = 0;
    while (mods[index]) {
      mods[index]--;
      index = (index + 1) % k;
      ans++;
    }
    return ans;
  }
};
