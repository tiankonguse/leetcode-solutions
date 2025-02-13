
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  int maxDifference(string s) {
    vector<int> stats(26, 0);
    for (auto c : s) {
      stats[c - 'a']++;
    }
    int ans = 0;
    vector<int> maxVal(2, 0);
    vector<int> minVal(2, INT_MAX);
    for (auto v: stats) {
      if (v) {
        maxVal[v % 2] = max(maxVal[v % 2], v);
        minVal[v % 2] = min(minVal[v % 2], v);
      }
    }
    return maxVal[1] - minVal[0];
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif