// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int Solver(int a, int b) {
    int ans = 1;

    while (a != b) {
      if (a > b) {
        a /= 2;
      } else {
        b /= 2;
      }
      ans++;
    }

    return ans;
  }

 public:
  vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries) {
    int m = queries.size();
    vector<int> ans(m, 0);
    for (int i = 0; i < m; i++) {
      ans[i] = Solver(queries[i][0], queries[i][1]);
    }

    return ans;
  }
};