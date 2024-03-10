// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
    int sum = 0;
    for (auto v : apple) {
      sum += v;
    }
    sort(capacity.begin(), capacity.end(),
         [](auto& a, auto& b) { return a > b; });
    int ans = 0;
    for (auto v : capacity) {
      sum -= v;
      ans++;
      if (sum <= 0) break;
    }
    return ans;
  }
};