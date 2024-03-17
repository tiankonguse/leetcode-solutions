// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long maximumValueSum(vector<int>& nums, int k,
                            vector<vector<int>>& edges) {
    int n = nums.size();
    int lastPos = -1;
    int num = 0;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      int& v = nums[i];
      if ((v ^ k) > v) {
        v = v ^ k;
        lastPos = i;
        num++;
      }
      sum += v;
    }

    if (num % 2 == 1) {
      int& v = nums[lastPos];
      sum -= v;
      v = v ^ k;
      sum += v;
      if (lastPos != 0) {
        swap(nums[0], nums[lastPos]);
      }
    }
    // for (int i = 0; i < n; i++) {
    //   int& v = nums[i];
    //   printf("%d ", v);
    // }
    ll ans = sum;
    // printf("sum=%lld\n", sum);

    if (num % 2 == 1) {  // 奇数个，最后肯定存在一个元素 k 的最高位是0
      for (int i = 1; i < n; i++) {
        // 尝试反转 [0, i]
        if (nums[0] + nums[i] < (nums[0] ^ k) + (nums[i] ^ k)) {
          ans = max(ans,
                    sum - (nums[0] + nums[i]) + (nums[0] ^ k) + (nums[i] ^ k));
        }
      }
    }
    return ans;
  }
};