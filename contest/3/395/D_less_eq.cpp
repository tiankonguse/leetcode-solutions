// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int medianOfUniquenessArray(vector<int>& nums) {
    ll n = nums.size();
    ll num = (1 + n) * n / 2;
    ll midPos = (num+1) / 2;

    unordered_map<int, int> h;
    for (auto v : nums) {
      h[v]++;
    }
    if (h.size() == 1) return 1;  // 全部相同

    int l = 1, r = h.size() + 1;  // 二分答案
    h.clear();
    // printf("l=%d r=%d midPos=%lld\n", l, r, midPos);
    while (l < r) {
      int mid = (l + r) / 2;
      int i = 0;
        // printf("l=%d r=%d mid=%d\n", l, r, mid);

      ll midNum = 0;  // 小于等于 mid 的个数
      h.clear();
      for (int j = 0; j < n; j++) {
        h[nums[j]]++;

        while (h.size() > mid) {
          h[nums[i]]--;
          if (h[nums[i]] == 0) {
            h.erase(nums[i]);
          }
          i++;
        }
        midNum += j - i + 1;
      }
        // printf("midNum=%lld\n", midNum);

      if (midNum < midPos) {
        l = mid + 1;
      } else{
        r = mid;
      }
    }
    return r;
  }
};