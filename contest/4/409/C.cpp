// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> shortestDistanceAfterQueries(int n,
                                           vector<vector<int>>& queries) {
    map<int, int> h;
    for (int i = n - 2; i >= 0; i--) {
      h[i] = i + 1;
    }
    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      int a = q[0], b = q[1];

      // 三种情况
      auto itBig = h.upper_bound(a);
      itBig--;

      // 1. 已存在更大的，忽略，答案不变
      if (itBig->first == a && itBig->second < b) {
        while (itBig != h.end() && itBig->second <= b) {
          h.erase(itBig++);
        }
        h[a] = b;
      }
      ans.push_back(h.size());
    }
    return ans;
  }
};