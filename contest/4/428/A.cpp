
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
  int buttonWithLongestTime(vector<vector<int>>& events) {
    int ans = 0;
    int D = 0;
    int pre = 0;
    for (auto& v : events) {
      int i = v[0];
      int t = v[1];
      int d = t - pre;
      pre = t;
      if (d > D) {
        D = d;
        ans = i;
      } else if (d == D && i < ans) {
        ans = i;
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<vector<int>>& jump, const int& ans) {
  TEST_SMP1(Solution, buttonWithLongestTime, ans, jump);
}

int main() {
  // Test([[1,2],[2,5],[3,9],[1,15], 3);
  return 0;
}

#endif