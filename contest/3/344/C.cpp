// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<int> colorTheArray(int n, vector<vector<int>>& queries) {
    vector<int> colors(n + 2, 0);
    vector<int> ans;
    ans.reserve(n);

    int now = 0;
    for (auto& q : queries) {
      int i = q[0] + 1;
      int c = q[1];

      if (colors[i] != 0) {
        if (colors[i] == colors[i - 1]) {
          now--;
        }
        if (colors[i] == colors[i + 1]) {
          now--;
        }
      }
      colors[i] = c;

      if (colors[i] == colors[i - 1]) {
        now++;
      }
      if (colors[i] == colors[i + 1]) {
        now++;
      }

      ans.push_back(now);
    }

    return ans;
  }
};