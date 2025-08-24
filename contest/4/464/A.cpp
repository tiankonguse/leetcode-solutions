
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
// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t);
  return y;
}
class Solution {
 public:
  int gcdOfOddEvenSums(ll n) {
    int oddLeft = 1, oddRight = 2 * n - 1;
    ll sumOdd = (oddLeft + oddRight) * n / 2;
    int evenLeft = 2, evenRight = 2 * n;
    ll sumEven = (evenLeft + evenRight) * n / 2;
    return Gcd(sumOdd, sumEven);
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