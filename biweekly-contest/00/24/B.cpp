// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  //  1 1 2 3 5 8 13
  // 1 2 3 4(3+1) 5 6(5+1) 7(5+2) 8 9(8+1) 10(8+2) 11(8+3) 12()
 public:
  int findMinFibonacciNumbers(int k) {
    vector<int> nums;
    nums.push_back(1);
    int pre = 1;
    while (nums.back() < k) {
      nums.push_back(nums.back() + pre);
      pre = nums.back() - pre;
    }

    int ans = 0;
    while (k > 0) {
      auto it = upper_bound(nums.begin(), nums.end(), k);
      it--;
      k -= *it;
      ans++;
    }
    return ans;
  }
};
