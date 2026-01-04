
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

typedef long long ll;
class Solution {
  vector<vector<int>> lists;
  vector<ll> medians;
  vector<ll> costs;
  int n;
  int M;
  ll Dfs(int mask) {
    if (costs[mask] != -1) {
      return costs[mask];
    }
  }

 public:
  ll minMergeCost(vector<vector<int>>& lists_) {
    lists.swap(lists_);
    n = lists.size();
    M = 1 << n;
    medians.resize(M, INT64_MAX);
    costs.resize(M, -1);
    return Dfs(M - 1);
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() { return 0; }

#endif