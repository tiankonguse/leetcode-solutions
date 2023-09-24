// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll maximumSumOfHeights(vector<int>& maxHeights) {
    int n = maxHeights.size();
    vector<ll> leftSum(n + 2, 0);
    vector<ll> rightSum(n + 2, 0);
    vector<ll> sta;
    sta.reserve(n + 2);

    auto Get1 = [&maxHeights, &n](int i) {
      if (i == 0 || i == n + 1) {
        return 0;
      }
      return maxHeights[i - 1];
    };

    // left sum
    // printf("step1\n");
    sta.push_back(0);
    for (int i = 1; i <= n; i++) {
      ll nowVal = Get1(i);
      while (nowVal <= Get1(sta.back())) {
        sta.pop_back();
      }
      leftSum[i] = leftSum[sta.back()] + nowVal * (i - sta.back());
      // printf("pre=%d presum=%lld dis=%d val=%lld leftsum=%lld\n", sta.back(),
      // leftSum[sta.back()], (i - sta.back()), nowVal, leftSum[i]);
      sta.push_back(i);
    }

    // printf("step2\n");
    sta.clear();
    sta.push_back(n + 1);
    for (int i = n; i >= 1; i--) {
      ll nowVal = Get1(i);
      while (nowVal <= Get1(sta.back())) {
        sta.pop_back();
      }
      rightSum[i] = rightSum[sta.back()] + nowVal * (sta.back() - i);
      sta.push_back(i);
    }

    // printf("step3\n");
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      ll nowVal = Get1(i);
      ans = max(ans, leftSum[i] + rightSum[i] - nowVal);
    }
    // printf("step4\n");
    return ans;
  }
};