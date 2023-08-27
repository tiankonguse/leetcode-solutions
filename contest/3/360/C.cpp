// #include <bits/stdc++.h>

#include "base.h"
using namespace std;


typedef long long ll;
class Solution {
  int SplitHighBit(int l, vector<int>& bits) {
    int r = l;
    while (bits[r] == 0) {
      r++;
    }

    int ans = r - l;
    while (r > l) {
      bits[r]--;
      bits[r - 1] += 2;
      r--;
    }
    return ans;
  }

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
    for (int i = 0; i < 31; i++) {
      printf("i=%d bit=%d\n", i, bits[i]);
    }

    int ans = 0;
    for (int i = 0; target > 0; i++) {
      printf("i=%d target=%d ans=%d\n", i, target, ans);
      if ((target >> i) & 1) {
        printf("bit=1, num=%d\n", bits[i]);
        if (bits[i] == 0) {
          printf("split high bits[i]=%d\n", bits[i]);
          ans += SplitHighBit(i, bits);
        }
        bits[i]--;
        target -= (1 << i);
      }
      bits[i + 1] += bits[i] / 2;
      printf("i=%d target=%d ans=%d\n", i, target, ans);
    }

    return ans;
  }
};