// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 0;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  int finalPositionOfSnake(int n, vector<string>& commands) {
    int x = 0, y = 0;
    for (auto& s : commands) {
      switch (s.front()) {
        case 'U':
          x--;
          break;
        case 'D':
          x++;
          break;
        case 'R':
          y++;
          break;
        case 'L':
          y--;
          break;
        default:
          break;
      }
    }
    return x * n + y;
  }
};