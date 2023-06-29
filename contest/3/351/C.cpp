// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  int numberOfGoodSubarraySplits(vector<int>& nums) {
    ll sum = accumulate(nums.begin(), nums.end(), 0ll);
    if (sum == 0) return 0;

    ll ans = 1;
    int flag = 0;  //  還沒有與到0
    ll num = 0;
    for (auto v : nums) {
      if (v % 2 == 0) {
        if (flag == 0) {
          continue;
        } else if (flag == 1) {
          num++;  // 零的个数
        } else {
        }
      } else {
        if (flag == 0) {
          flag = 1;  // 遇到1，开始自己算答案
          num = 1;
        } else if (flag == 1) {
          ans = (ans * num) % mod;
          num = 1;
        } else {
        }
      }
    }
    return ans;
  }
};