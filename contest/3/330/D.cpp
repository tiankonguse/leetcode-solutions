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

    for (int i = 1; i <= n + 1; i++) {
      for (int j = 1; j <= n + 1; j++) {
        leftLess[i][j] = rightGreat[i][j] = 0;
      }
    }

    vector<int> h(n + 2, 0);
    for (int i = 1; i <= n; i++) {
      h[nums[i - 1]] = i;
    }

    vector<int> leftFlag(n + 1, 0);
    for (int j = 1; j <= n; j++) {
      for (int v = 1; v <= n; v++) {
        leftLess[j][v] = leftLess[j][v - 1];
        if (leftFlag[v - 1]) {
          leftLess[j][v]++;
        }
      }
      leftFlag[nums[j - 1]] = 1;
    }

    vector<int> rightFlag(n + 2, 0);
    for (int k = n; k >= 1; k--) {
      for (int v = n; v >= 1; v--) {
        rightGreat[k][v] = rightGreat[k][v + 1];
        if (rightFlag[v + 1]) {
          rightGreat[k][v]++;
        }
      }
      rightFlag[nums[k - 1]] = 1;
    }

    ll ans = 0;
    for (int j = 1; j <= n; j++) {
      for (int k = j + 1; k <= n; k++) {
        if (nums[j - 1] < nums[k - 1]) continue;
        ans += leftLess[j][nums[k - 1]] * rightGreat[k][nums[j - 1]];
      }
    }

    return ans;
  }
};