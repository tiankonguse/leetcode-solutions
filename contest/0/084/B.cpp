// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  string findReplaceString(string s, vector<int>& indices,
                           vector<string>& sources, vector<string>& targets) {
    int k = indices.size();
    vector<pair<int, int>> indexs(k);
    for (int i = 0; i < k; i++) {
      indexs[i] = {i, indices[i]};
    }
    sort(indexs.begin(), indexs.end(),
         [](auto& a, auto& b) { return a.second < b.second; });
    const char* p = s.data();
    for (int i = 0; i < k; i++) {
      int index = indexs[i].first;
      int offset = indices[index];
      const string& source = sources[index];
      if (strncmp(p + offset, source.data(), source.size()) != 0) {
        indices[index] = -1;
      }
    }

    string ans;

    int si = 0;
    for (int i = 0; i < k; i++) {
      int index = indexs[i].first;
      int offset = indices[index];
      if (offset == -1) continue;

      if (si < offset) {
        ans.append(s.substr(si, offset - si));
        si = offset;
      }

      ans.append(targets[index]);
      si = offset + sources[index].size();
    }

    if (si < s.size()) {
      ans.append(s.substr(si));
    }
    return ans;
  }
};