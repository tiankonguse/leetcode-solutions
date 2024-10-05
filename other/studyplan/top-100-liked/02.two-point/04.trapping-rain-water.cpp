// #include <bits/stdc++.h>
/*
题目: 42. 接雨水
地址:
https://leetcode.cn/problems/trapping-rain-water/description/?envType=study-plan-v2&envId=top-100-liked
考察: 双指针
问题:  平面接雨水.
思路1: 单调递减栈
时间复杂度: `O(n)`
空间复杂度: `O(n)`
思路2: 预处理左右max，枚举每一列接多少水
时间复杂度: `O(n)`
空间复杂度: `O(n)`
思路3: 左右指针维护当前左右的max
时间复杂度: `O(n)`
空间复杂度: `O(1)`
*/

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
  int MonotoneStack(const vector<int>& height) {
    int ans = 0;
    stack<pair<int, int>> sta;
    sta.push({0, -1});
    for (int rightX = 0; rightX < height.size(); rightX++) {
      int rightH = height[rightX];
      while (rightH >= sta.top().first) {
        if (sta.size() == 1) {
          sta.pop();
          break;
        }
        auto [midH, midX] = sta.top();
        sta.pop();
        auto [leftH, leftX] = sta.top();

        ans += (min(leftH, rightH) - midH) * (rightX - leftX - 1);
      }
      sta.push({rightH, rightX});
    }
    return ans;
  }
  int PreprocessingMaximumValue(const vector<int>& height) {
    int n = height.size();
    vector<int> leftMax(n, 0);
    vector<int> rightMax(n, 0);
    int preMax = 0;

    preMax = 0;
    for (int i = 0; i < n; i++) {
      leftMax[i] = preMax = max(preMax, height[i]);
    }
    preMax = 0;
    for (int i = n - 1; i >= 0; i--) {
      rightMax[i] = preMax = max(preMax, height[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      ans += min(leftMax[i], rightMax[i]) - height[i];
    }
    return ans;
  }
  int TwoPoint(const vector<int>& height) {
    int leftMax = 0, rightMax = 0;
    int l = 0, r = height.size() - 1;
    int ans = 0;
    while (l <= r) {
      leftMax = max(leftMax, height[l]);
      rightMax = max(rightMax, height[r]);
      if (leftMax < rightMax) {
        ans += leftMax - height[l];
        l++;
      } else {
        ans += rightMax - height[r];
        r++;
      }
    }
    return ans;
  }

 public:
  int trap(const vector<int>& height) {
    return TwoPoint(height);  //
  }
};