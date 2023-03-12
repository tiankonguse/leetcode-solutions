// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumRecolors(string blocks, int k) {
    int w = 0;
    int n = blocks.size();
    for (int i = 0; i < k - 1; i++) {
      if (blocks[i] == 'W') {
        w++;
      }
    }

    int ans = k;
    for (int i = k - 1; i < n; i++) {
      if (blocks[i] == 'W') {
        w++;
      }
      ans = min(ans, w);
      if (blocks[i - k + 1] == 'W') {
        w--;
      }
    }
    return ans;
  }
};