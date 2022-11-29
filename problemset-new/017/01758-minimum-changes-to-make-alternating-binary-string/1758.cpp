#include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
  int Cal(const string& s, int v) {
    int ans = 0;
    for (auto c : s) {
      if (c - '0' != v) ans++;
      v = 1 - v;
    }

    return ans;
  }

 public:
  int minOperations(const string& s) { return min(Cal(s, 0), Cal(s, 1)); }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
