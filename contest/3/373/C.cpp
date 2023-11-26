// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
    int n = nums.size();
    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n; i++) {
      vec[i] = {nums[i], i};
    }
    sort(vec.begin(), vec.end());

    vector<int> index(n);
    for (int i = 0; i < n; ) {
      int pos = i;
      index.clear();
      while (i < n && (index.empty() ||
                       nums[vec[i].second] - nums[index.back()] <= limit)) {
        index.push_back(vec[i].second);
        i++;
      }
      sort(index.begin(), index.end());
      for (auto j : index) {
        nums[j] = vec[pos].first;
        pos++;
      }
    }

    return nums;
  }
};