// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int beautifulSubstrings(const string& s, int k) {
    set<char> h = {'a', 'e', 'i', 'o', 'u'};

    int n = s.size();
    vector<pair<int, int>> nums(n+1, make_pair<int, int>(0, 0));
    for (int i = 1; i <= n; i++) {
      nums[i] = nums[i - 1];
      if (h.count(s[i - 1])) {
        nums[i].first++;
      } else {
        nums[i].second++;
      }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j ++) {
        int a = nums[j].first - nums[i - 1].first;
        int b = nums[j].second - nums[i - 1].second;
        if (a == b && (a * b) % k == 0) {
          ans++;
        }
      }
    }
    return ans;
  }
};