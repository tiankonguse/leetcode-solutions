// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int miceAndCheese(vector<int>& nums1, vector<int>& nums2, int k) {
    int n = nums1.size();
    vector<pair<int, int>> scores(n);

    int ans = 0;
    for (int i = 0; i < n; i++) {
      scores[i] = {nums1[i] - nums2[i], i};
      ans += nums2[i];
    }
    sort(scores.begin(), scores.end(),
         [](auto& a, auto& b) { return a.first > b.first; });

    for (int i = 0; i < k; i++) {
      printf("i=%d p=%d score=%d\n", i, scores[i].second, scores[i].first);
      ans += scores[i].first;
    }
    return ans;
  }
};