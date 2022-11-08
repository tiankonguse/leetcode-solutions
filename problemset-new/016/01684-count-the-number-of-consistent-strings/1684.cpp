#include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
 public:
  int countConsistentStrings(string allowed, vector<string>& words) {
    vector<int> s(26, 0);
    for (char c : allowed) {
      s[c - 'a'] = 1;
    }

    int ans = 0;
    for (auto& str : words) {
      int have = 1;
      for (char c : str) {
        if (s[c - 'a'] == 0) {
          have = 0;
          break;
        }
      }
      ans += have;
    }
    return ans;
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
