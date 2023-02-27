// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> divisibilityArray(const string& word, int m) {
    int n = word.size();
    vector<int> ans;
    ans.reserve(n);
    ll pre = 0;
    for (auto c : word) {
      ll v = c - '0';
      pre = (pre * 10 + v) % m;
      ans.push_back(pre % m == 0);
    }
    return ans;
  }
};