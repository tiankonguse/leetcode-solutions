// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minOperations(vector<int>& nums, int target) {
    ll sum = 0;
    for (auto v : nums) {
      sum += v;
    }
    if (sum < target) {
      return -1;
    }
    unordered_map<ll, int> h;
    for (int i = 0; i <= 30; i++) {
      ll base = 1;
      ll v = base << i;
      h[v] = i;
    }

    vector<int> bits(34, 0);
    for (auto v : nums) {
      bits[h[v]]++;
    }

    int ans = 0;
    for (int i = 0; i <= 31; i++) {
      if ((target >> i) & 1) {
        bits[i]--;
        target -= (1 << i);
      }
      if (bits[i] > 0) {
        bits[i + 1] += bits[i] / 2;
      } else if (bits[i] < 0) {
        bits[i + 1] -= (1 - bits[i]) / 2;
        ans++;
      }
    }

    return ans;
  }
};