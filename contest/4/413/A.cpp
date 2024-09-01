// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  bool checkTwoChessboards(const string& p1, const string& p2) {
    auto fix = [](const string& p) -> int {
      int x = p[0] - 'a';
      int y = p[1] - '1';
      return (x + y) % 2;
    };
    return fix(p1) == fix(p2);
  }
};