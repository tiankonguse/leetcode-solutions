// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  unordered_map<int, int> m;
  int Cal(int p) {
    if (m.count(p)) {
      return m[p];
    }

    if (p % 2 == 0) {
      return m[p] = Cal(p / 2) + 1;
    } else {
      return m[p] = Cal(p * 3 + 1) + 1;
    }
  }

 public:
  int getKth(int lo, int hi, int k) {
    m[1] = 0;

    vector<pair<int, int>> ans;
    for (int i = lo; i <= hi; i++) {
      ans.push_back({Cal(i), i});
    }
    sort(ans.begin(), ans.end());
    return ans[k - 1].second;
  }
};