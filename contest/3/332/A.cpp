// #include <bits/stdc++.h>

#include "base.h"
using namespace std;
/*
给你一个下标从 0 开始的整数数组 nums 。

现定义两个数字的 串联 是由这两个数值串联起来形成的新数字。

例如，15 和 49 的串联是 1549 。
nums 的 串联值 最初等于 0 。执行下述操作直到 nums 变为空：

如果 nums 中存在不止一个数字，分别选中 nums
中的第一个元素和最后一个元素，将二者串联得到的值加到 nums 的 串联值 上，然后从
nums 中删除第一个和最后一个元素。 如果仅存在一个元素，则将该元素的值加到 nums
的串联值上，然后删除这个元素。 返回执行完所有操作后 nums 的串联值。
*/

typedef long long ll;
class Solution {
  ll Sum(ll a, ll b) {
    int B = b;
    while (B) {
      a *= 10;
      B /= 10;
    }
    return a + b;
  }

 public:
  long long findTheArrayConcVal(vector<int>& nums) {
    ll ans = 0;

    int l = 0, r = nums.size() - 1;
    while (l <= r) {
      if (l == r) {
        ans += nums[l];
      } else {
        ans += Sum(nums[l], nums[r]);
      }
      l++, r--;
    }

    return ans;
  }
};