
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

/*
You are given a positive integer n representing an n x n cargo deck on a ship. Each cell on the deck can hold one
container with a weight of exactly w.

However, the total weight of all containers, if loaded onto the deck, must not exceed the ship's maximum weight
capacity, maxWeight.

Return the maximum number of containers that can be loaded onto the ship.
*/
typedef long long ll;
class Solution {
 public:
  int maxContainers(ll n, ll w, ll maxWeight) {
    ll totalWeight = 0;
    if (n * n * w <= maxWeight) {
      return n * n;
    } else {
      return maxWeight / w;
    }
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