// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> numberOfPairs(vector<int>& nums) {
    set<int> m;

    int ans1 = 0, ans2 = 0;
    for (auto v : nums) {
      if (m.count(v)) {
        m.erase(v);
        ans1++;
      } else {
        m.insert(v);
      }
    }
    ans2 = m.size();
    return {ans1, ans2};
  }
};