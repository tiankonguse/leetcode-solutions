// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int toNum(const string& s) {
    const int h = (s[0] - '0') * 10 + (s[1] - '0');
    const int m = (s[2] - '0') * 10 + (s[3] - '0');
    return h * 60 + m;
  }
  bool Check(vector<int>& times) {
    int n = times.size();
    for (int i = 0; i < n; i++) {
      if (i + 2 < n && times[i + 2] < times[i] + 60) {
        return true;
      }
    }
    return false;
  }

 public:
  vector<string> findHighAccessEmployees(vector<vector<string>>& access_times) {
    sort(access_times.begin(), access_times.end());

    unordered_map<string, vector<int>> m;
    for (auto& v : access_times) {
      const string& name = v[0];
      m[name].push_back(toNum(v[1]));
    }

    vector<string> ans;
    for (auto& [name, times] : m) {
      if (Check(times)) {
        ans.push_back(name);
      }
    }

    return ans;
  }
};