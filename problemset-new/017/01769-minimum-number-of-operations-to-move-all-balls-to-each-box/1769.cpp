#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> minOperations(string& s) {
    int n = s.size();
    vector<int> ans(n, 0);
    int l = 0, r = 0;

    int sum = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == '1') {
        r++;
        sum += i;
      }
    }

    for (int i = 0; i < n; i++) {  // (0,l) [r,n)
      ans[i] = sum;
      if (s[i] == '1') {
        l++;
        r--;
      }

      sum -= r;
      sum += l;
    }

    return ans;
  }
};