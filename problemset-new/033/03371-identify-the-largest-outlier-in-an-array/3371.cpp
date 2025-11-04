
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
  int getLargestOutlier(vector<int>& nums) {
    int sum = 0;
    int ans = nums.front();
    unordered_map<int, int> h;
    for (auto v : nums) {
      sum += v;
      h[v]++;
      ans = min(ans, v);
    }
    for (auto a : nums) {
      int tmp = sum - a;
      if (tmp % 2 != 0) continue;
      int b = tmp / 2;
      if (!h.count(b)) continue;
      if (b == a && h[b] == 1) {
        continue;
      }
      ans = max(ans, a);
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) { TEST_SMP1(Solution, getLargestOutlier, ans, jump); }

int main() {
  Test({2, 3, 5, 10}, 10);
  Test({-2, -1, -3, -6, 4}, 4);
  Test({1, 1, 1, 1, 1, 5, 5}, 5);
  Test({6, -31, 50, -35, 41, 37, -42, 13}, -35);
  return 0;
}

#endif

/*
6,-31,50,-35,41,37,-42
,13

*/