// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int countDays(int n, vector<vector<int>>& meetings) {
    sort(meetings.begin(), meetings.end());

    int ans = 0;
    int pre = 1;
    for (auto& v : meetings) {
      int a = v[0], b = v[1];
      pre = max(pre, a);
      ans += max(0, b - pre + 1);
      pre = max(pre, b+1);
    }
    return n - ans;
  }
};