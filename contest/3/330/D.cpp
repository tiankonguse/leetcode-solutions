// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
ll leftLess[4002][4002];
ll rightGreat[4002][4002];
class Solution {
 public:
  long long countQuadruplets(vector<int>& nums) {
    int n = nums.size();

    memset(leftLess, 0, sizeof(leftLess));
    memset(rightGreat, 0, sizeof(rightGreat));

    for (int i = 1; i <= n; i++) {
      leftLess[i][nums[i - 1]] = rightGreat[i][nums[i - 1]] = 1;
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        leftLess[i][j] = leftLess[i-1][j] + leftLess[i][j-1] - leftLess[i-1][j-1];
      }
    }

    for(int i=n;i>=1;i--){
      for(int j=n;j>=1;j--){
        rightGreat[i][j] = rightGreat[i+1][j] + rightGreat[i][j+1] - rightGreat[i+1][j+1];
      }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        if (nums[i-1] < nums[j-1]) continue;
        ans += leftLess[i-1][nums[j-1]-1] * rightGreat[j+1][nums[i-1]+1];
      }
    }

    return ans;
  }
};