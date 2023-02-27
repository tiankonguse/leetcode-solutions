// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
 public:
  string alphabetBoardPath(string target) {
    vector<string> paths = {"abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"};
    unordered_map<char, pair<int, int>> h;
    for (int i = 0; i < paths.size(); i++) {
      for (int j = 0; j < paths[i].length(); j++) {
        char c = paths[i][j];
        h[c] = {i, j};
      }
    }

    pair<int, int> pre = {0, 0};
    string ans;
    for (auto c : target) {
      while (pre.first > h[c].first) {
        pre.first--;
        ans.push_back('U');
      }
      while (pre.second > h[c].second) {
        pre.second--;
        ans.push_back('L');
      }
      while (pre.second < h[c].second) {
        pre.second++;
        ans.push_back('R');
      }
      while (pre.first < h[c].first) {
        pre.first++;
        ans.push_back('D');
      }
      ans.push_back('!');
    }
    return ans;
  }
};
