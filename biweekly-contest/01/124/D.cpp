// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxSelectedElements(vector<int>& nums) {
    int n = nums.size();
    int ans = 1;
    unordered_map<int, int> h;
    sort(nums.begin(), nums.end());
    for (int i = n - 1; i >= 0; i--) {
      for (int k = 0; k <= 1; k++) {
        int v = nums[i] + k;
        h[v] = max(h[v], 1 + h[v + 1]);
        ans = max(ans, h[v]);
      }
    }

    return ans;
  }
};