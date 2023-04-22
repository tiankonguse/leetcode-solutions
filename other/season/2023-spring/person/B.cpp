// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  unordered_set<string> h;
  string name;
  int Add(const string& names) {
    int num = 0;

    for (auto c : names) {
      if (c == '-') {
        if (h.count(name) == 0) {
          num++;
          h.insert(name);
        }
        name.clear();
      } else if (c == '>') {
        continue;
      } else {
        name.push_back(c);
      }
    }

    if (h.count(name) == 0) {
      num++;
      h.insert(name);
    }
    name.clear();

    return num;
  }

 public:
  int adventureCamp(vector<string>& expeditions) {
    int n = expeditions.size();
    h.insert("");
    Add(expeditions[0]);
    // printf("0 -> %d\n", h.size());
    int ans = -1;
    int ansNum = 0;
    for (int i = 1; i < expeditions.size(); i++) {
      int num = Add(expeditions[i]);
      if (num > ansNum) {
        ansNum = num;
        ans = i;
      }
      // printf("%d -> %d\n", i, h.size());
    }
    return ans;
  }
};