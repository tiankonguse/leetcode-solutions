// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
  int Solver(int a, int b, int c) {
    vector<int> bit;
    while (a) {
      bit.push_back(a & 1);
      a /= 2;
    }
    while (b) {
      bit.push_back(b & 1);
      b /= 2;
    }
    while (c) {
      bit.push_back(c & 1);
      c /= 2;
    }
    std::reverse(bit.begin(), bit.end());
    int ans = 0;
    for (auto v : bit) {
      ans = ans * 2 + v;
    }
    return ans;
  }

 public:
  int maxGoodNumber(vector<int>& nums) {
    int a = nums[0], b = nums[1], c = nums[2];
    int ans = 0;
    ans = max(ans, Solver(a, b, c));
    ans = max(ans, Solver(a, c, b));
    ans = max(ans, Solver(b, a, c));
    ans = max(ans, Solver(b, c, a));
    ans = max(ans, Solver(c, a, b));
    ans = max(ans, Solver(c, b, a));
    return ans;
  }
};