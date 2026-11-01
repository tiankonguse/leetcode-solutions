
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
  ll minimumMaxValue(ll n, const ll index, const ll value) {
    if (value == 1) return -1;
    const ll minPrime = PrimeFactorization(value);
    // MyPrintf("minPrime = %lld\n", minPrime);
    if (minPrime == 2) {
      ll preNum = value / 2;
      if (index >= preNum) return -1;
      return value + (n - 1 - index) * 2;
    } else {
      if (index > 0) {  // 向前检查
        ll preIndex = index - 1;
        ll preVal = value - minPrime;
        ll preNum = preVal / 2;
        if (preIndex >= preNum) return -1;
      }
      if (index == n - 1) {
        return value;
      }
      ll nextIndex = index + 1;
      ll nextVal = value + minPrime;
      return nextVal + (n - 1 - nextIndex) * 2;
    }
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