// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int countDays(int n, vector<vector<int>>& meetings) {
    sort(meetings.begin(), meetings.end(), [](auto& a, auto& b) {
      if (a[0] == b[0]) {
        return a[1] < b[1];
      } else {
        return a[0] < b[0];
      }
    });

    int ans = 0;
    int pre = 0;
    for (auto& v : meetings) {
      int a = v[0], b = v[1];
      if (pre < a) {
        ans += a - pre - 1;
      }
      pre = max(pre, b);
    }
    if (pre < n) {
      ans += n - pre;
    }
    return ans;
  }
};