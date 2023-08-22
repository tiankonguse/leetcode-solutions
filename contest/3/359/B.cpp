// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumSum(int n, int k) {
    unordered_set<int> h;
    int v = 0;
    int ans = 0;
    while (h.size() < n) {
      v++;
      if (v < k && h.count(k - v)) {
        continue;
      }
      h.insert(v);
      ans += v;
    }
    return ans;
  }
};
