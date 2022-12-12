// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int beautySum(const string& s) {
    int ans = 0;
    int n = s.size();

    for (int i = 0; i < n; i++) {
      vector<int> counts(26, 0);
      for (int j = i; j < n; j++) {
        counts[s[j] - 'a']++;
        int maxNum = 0, minNum = n;
        for (int c : counts) {
          if (c == 0) continue;
          maxNum = max(maxNum, c);
          minNum = min(minNum, c);
        }
        ans += maxNum - minNum;
      }
    }
    return ans;
  }
};
