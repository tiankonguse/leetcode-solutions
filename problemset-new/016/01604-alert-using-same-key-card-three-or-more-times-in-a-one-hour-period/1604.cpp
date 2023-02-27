// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  // HH:MM
  int V(char a, char b) { return (a - '0') * 10 + (b - '0'); }
  int M(const string& s) { return V(s[0], s[1]) * 60 + V(s[3], s[4]); }
  bool Check(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    for (int i = 2; i < nums.size(); i++) {
      if (nums[i] - nums[i - 2] <= 60) {
        return true;
      }
    }
    return false;
  }

 public:
  vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
    map<string, vector<int>> m;
    for (int i = 0; i < keyName.size(); i++) {
      m[keyName[i]].push_back(M(keyTime[i]));
    }
    vector<string> ans;
    for (auto& [k, vs] : m) {
      if (Check(vs)) {
        ans.push_back(k);
      }
    }
    sort(ans.begin(), ans.end());
    return ans;
  }
};