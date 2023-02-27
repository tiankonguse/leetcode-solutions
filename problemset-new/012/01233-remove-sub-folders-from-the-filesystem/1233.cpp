// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<string> removeSubfolders(vector<string>& folder) {
    sort(folder.begin(), folder.end());
    vector<string> ans;
    ans.reserve(folder.size());

    string pre = "//";
    for (auto& s : folder) {
      if (s.size() > pre.size() &&
          strncmp(pre.data(), s.data(), pre.size()) == 0) {
        continue;
      }
      ans.push_back(s);
      pre = s + "/";
    }

    return ans;
  }
};