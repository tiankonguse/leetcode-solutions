// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long findMaximumElegance(vector<vector<int>>& items, int k) {
    sort(items.begin(), items.end(), [](auto& a, auto& b) {
      if (a[1] == b[1]) {
        return a[0] > b[0];
      } else {
        return a[1] < b[1];
      }
    });
    int preCategory = 0;
    for (auto& v : items) {
      if (v[1] != preCategory) {
        v[0]++;
      }
      preCategory = v[1];
    }
    sort(items.begin(), items.end(),
         [](auto& a, auto& b) { return a[0] > b[0]; });
    long long ans = 0;
    for (int i = 0; i < k; i++) {
      ans += items[i][0];
    }
    return ans;
  }
};
