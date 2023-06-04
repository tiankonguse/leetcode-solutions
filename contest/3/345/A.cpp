// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> circularGameLosers(int n, int k) {
    vector<int> nums(n, 0);
    ll now = 0;
    ll step = 0;
    while (nums[now]) {
      nums[now]++;
      step++;
      now = (now + step * k) % n;
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
      if (nums[i] == 0) {
        ans.push_back(i + 1);
      }
    }
    return ans;
  }
};