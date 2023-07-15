// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
 public:
  bool checkArray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<ll> dis(n * 2 + 1, 0);
    ll pre = 0;
    for (int i = 0; i < n; i++) {
      ll v = pre + nums[i];
      if (v < 0) return false;
      if (v > 0) {
        pre -= v;
        dis[i + k - 1] += v;
      }
      pre += dis[i];
    }
    for (int i = n; i < dis.size(); i++) {
      if (dis[i] > 0) return false;
    }
    return true;
  }
};