// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> vowelStrings(vector<string>& words,
                           vector<vector<int>>& queries) {
    set<char> h = {'a', 'e', 'i', 'o', 'u'};
    int n = words.size();
    vector<int> sums;
    sums.reserve(n + 1);
    sums.push_back(0);
    for (auto& s : words) {
      if (h.count(s.front()) && h.count(s.back())) {
        sums.push_back(sums.back() + 1);
      } else {
        sums.push_back(sums.back());
      }
    }

    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      int l = q[0] + 1, r = q[1] + 1;
      ans.push_back(sums[r] - sums[l - 1]);
    }
    return ans;
  }
};