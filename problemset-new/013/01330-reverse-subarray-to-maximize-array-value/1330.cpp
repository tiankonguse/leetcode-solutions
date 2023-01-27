// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  // 减少的值=abs(a[l]−a[l−1])+abs(a[r]−a[r+1]);
  // 增加的值=abs(a[l-1]-a[r])+abs(a[l]-a[r+1]);
  // 变化的值=abs(a[l−1]−a[r])+abs(a[l]−a[r+1])−(abs(a[l]−a[l−1])+abs(a[r]−a[r+1]));

  // 增加的值=abs(a[l−1]−a[r])+abs(a[l]−a[r+1])
  // ans ={
  //   a[l−1]+a[l]−(a[r]+a[r+1]),
  //   a[l−1]−a[l]−(a[r]−a[r+1]),
  //  −a[l−1]+a[l]−(−a[r]+a[r+1]),
  //  −a[l−1]−a[l]−(−a[r]−a[r+1])
  // } - abs(a[l]−a[l−1]) - abs(a[r]−a[r+1])

  vector<int> nums;

  ll A(int i, int j) { return abs(nums[i] - nums[j]); }

  int maxValueAfterReverse(vector<int>& nums_) {
    nums.swap(nums_);
    int n = nums.size();
    ll baseAns = 0;
    for (int i = 1; i < n; i++) {
      baseAns += A(i - 1, i);
    }

    ll maxDis = 0;

    for (int i = 1; i < n; i++) {  // 反转前缀
      ll tmp = -A(i - 1, i) + A(0, i);
      maxDis = max(maxDis, tmp);
    }
    for (int i = 1; i < n; i++) {  // 反转后缀
      ll tmp = -A(i - 1, i) + A(i - 1, n - 1);
      maxDis = max(maxDis, tmp);
    }

    int dir[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (int i = 0; i < 4; i++) {  //
      ll maxVal = INT_MIN;
      ll minVal = INT_MAX;
      for (int j = 1; j < n; j++) {
        ll v = nums[j - 1] * dir[i][0] + nums[j] * dir[i][1];
        ll cur = A(j - 1, j);
        maxVal = max(maxVal, v - cur);
        minVal = min(minVal, v + cur);
      }
      maxDis = max(maxDis, maxVal - minVal);
    }

    return baseAns + maxDis;
  }
};
