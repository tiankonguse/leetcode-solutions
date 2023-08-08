// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numberOfEmployeesWhoMetTarget(vector<int>& hours, int target) {
    int ans = 0;
    for (auto v : hours) {
      if (v >= target) {
        ans++;
      }
    }
    return ans;
  }
};