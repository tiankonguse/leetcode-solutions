// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int S(int x) { return x * x; }

 public:
  vector<int> countPoints(vector<vector<int>>& points,
                          vector<vector<int>>& queries) {
    vector<int> ans;
    for (auto& q : queries) {
      int x = q[0], y = q[1], r = q[2];
      int n = 0;
      for (auto& p : points) {
        int X = p[0], Y = p[1];
        if (S(x - X) + S(y - Y) <= r * r) {
          n++;
        }
      }
      ans.push_back(n);
    }

    return ans;
  }
};
