// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());

    auto Check = [&nums1, &nums2](int a, int b) -> pair<bool, int> {
      bool findAns = false;
      int ans = 0;
      for (int i = 0, j = 0; i < nums2.size(); i++,j++) {
        while (j == a || j == b) {
          j++;
        }
        int tmp = nums2[i] - nums1[j];

        if (!findAns) {
          findAns = true;
          ans = tmp;
        } else {
          if (ans != tmp) {
            return {false, 0};
          }
        }
      }
      return {true, ans};
    };

    int ans = INT_MAX;
    for (int i = 0; i < nums1.size(); i++) {
      for (int j = i + 1; j < nums1.size(); j++) {
        auto [flag, tmp] = Check(i, j);
        if (flag) {
          ans = min(ans, tmp);
        }
      }
    }
    return ans;
  }
};