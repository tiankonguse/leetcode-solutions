// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
ll leftLess[4001][4001];
ll rightGreat[4001][4001];
class Solution {
  void AppendSort(vector<ll>& nums, int v) {
    nums.push_back(v);
    for (int k = nums.size() - 1; k > 0; k--) {
      if (nums[k] > nums[k - 1]) {
        break;
      }
      swap(nums[k], nums[k - 1]);
    }
  }

 public:
  long long countQuadruplets(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        leftLess[i][j] = rightGreat[i][j] = 0;
      }
    }

    vector<ll> pre;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (nums[i] < nums[j]) continue;
        leftLess[i][j] =
            upper_bound(pre.begin(), pre.end(), nums[j]) - pre.begin();
      }
      AppendSort(pre, nums[i]);
    }

    vector<ll> suf;
    for (int j = n - 1; j >= 0; j--) {
      for (int i = j - 1; i >= 0; i--) {
        if (nums[i] < nums[j]) continue;
        rightGreat[i][j] =
            suf.end() - upper_bound(suf.begin(), suf.end(), nums[i]);
      }
      AppendSort(suf, nums[j]);
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (nums[i] < nums[j]) continue;
        ans += leftLess[i][j] * rightGreat[i][j];
      }
    }

    return ans;
  }
};