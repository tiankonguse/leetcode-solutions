// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

/*
 * // This is the custom function interface.
 * // You should not implement it, or speculate about its implementation
 */

class CustomFunction {
 public:
  // Returns f(x, y) for any given positive integers x and y.
  // Note that f(x, y) is increasing with respect to both x and y.
  // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
  int f(int x, int y) { return 0; }
};

typedef long long ll;

class Solution {
 public:
  vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
    vector<vector<int>> ans;
    for (int i = 1; i <= 1000; i++) {
      int l = 1, r = 1001;
      while (l < r) {
        int mid = (l + r) / 2;
        int Z = customfunction.f(i, mid);
        if (Z < z) {
          l = mid + 1;
        } else if (Z > z) {
          r = mid;
        } else {
          ans.push_back({i, mid});
          break;
        }
      }
    }
    return ans;
  }
};