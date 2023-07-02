// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int sumImbalanceNumbers(vector<int>& nums) {
    int ans = 0;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
      map<int, int> h;
      int tmpAns = 0;
      for (int j = i; j < n; j++) {
        int v = nums[j];
        h[v]++;

        auto it = h.find(v);
        if (it->second == 1) {
          auto next = it;
          auto pre = it;

          next++;

          if (it == h.begin() && next == h.end()) {  // 只有一个元素
            // do nothing
          } else if (it == h.begin()) {
            int nextVal = next->first;
            if (nextVal - v > 1) {
              tmpAns++;
            }
          } else if (next == h.end()) {  // 最后一个元素
            pre--;
            int preVal = pre->first;
            if (v - preVal > 1) {
              tmpAns++;
            }
          } else {  // 中间的元素
            pre--;
            int preVal = pre->first;
            int nextVal = next->first;

            if (nextVal - v > 1 && v - preVal > 1) {
              tmpAns++;
            } else if (nextVal - v <= 1 && v - preVal <= 1) {
              tmpAns--;
            }
          }
        }

        ans += tmpAns;
      }
    }

    return ans;
  }
};