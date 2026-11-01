
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
  ll PrimeFactorization(ll value) {
    ll e = (ll)(sqrt(0.0 + value) + 1);
    for (ll i = 2; i <= e && i <= value; i++) {
      if (value % i == 0) {
        return i;
      }
    }
    return value;
  }

 public:
  ll minimumMaxValue(int n, int index, int value) {
    if (value == 1) return -1;
    ll minPrime = PrimeFactorization(value);
    ll preNum = value / minPrime;
    if (index >= preNum) return -1;
    return value + (n - 1 - index) * minPrime;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif