// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  int numberOfGoodPartitions(vector<int>& nums) {
    unordered_map<int, int> H;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      const int v = nums[i];
      H[v] = i;
    }

    int num = 0;
    for (int i = 0; i < n;i++) {
      int l = i, r = H[nums[i]];
      while (l < r) {
        r = max(r, H[nums[l]]);
        l++;
      }
      i = r;
      num++;
    }

    int ans = 1;
    while (--num) {
      ans = (ans * 2) % mod;
    }
    return ans;
  }
};