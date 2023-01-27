// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<vector<int>> sortTheStudents(vector<vector<int>>& score, int k) {
    sort(score.begin(), score.end(),
         [k](const auto& a, const auto& b) { return a[k] > b[k]; });
    return score;
  }
};
