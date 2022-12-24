#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumSize(vector<int>& nums, int maxOperations) {
    ll l = 1, r = 1;
    for (ll v : nums) {
      r = max(r, v);
    }
    r++;

    // printf("l=%d r=%d\n", l, r);
    while (l < r) {
      ll mid = (l + r) / 2;
      ll num = 0;
      for (ll v : nums) {
        num += (v + mid - 1) / mid - 1;
      }
      if (num <= maxOperations) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return r;
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
