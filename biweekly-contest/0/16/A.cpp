// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int captureForts(vector<int>& forts) {
    int ans = 0;
    int n = forts.size();

    // 左->右
    for (int i = 0; i < n; i++) {
      if (forts[i] != 1) continue;
      int j = i + 1;
      while (j < n && forts[j] == 0) j++;  // skip 0
      if (j < n && forts[j] == -1) {
        ans = max(ans, j - i - 1);
      }
    }

    // 右->左
    for (int i = n - 1; i >= 0; i--) {
      if (forts[i] != 1) continue;
      int j = i - 1;
      while (j >= 0 && forts[j] == 0) j--;
      if (j >= 0 && forts[j] == -1) {
        ans = max(ans, i - j - 1);
      }
    }

    return ans;
  }
};