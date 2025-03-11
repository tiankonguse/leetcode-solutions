
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
  int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
    int n = fruits.size();
    int m = baskets.size();
    set<pair<int, int>> basketsSet;
    for (int i = 0; i < m; i++) {
      basketsSet.insert({baskets[i], i});
    }

    int ans = 0;
    for (auto v : fruits) {
      auto it = basketsSet.lower_bound({v, -1});
      if (it != basketsSet.end()) {
        basketsSet.erase(it);
      } else {
        ans++;
      }
    }

    return ans;
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