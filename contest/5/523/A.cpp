
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
 public:
  bool threeFibonacciSum(int n) {
    ll a = 0, b = 1;
    const ll maxVal = 1e9;
    unordered_set<ll> h;
    while (b <= maxVal) {
      b = a + b;
      a = b - a;
      h.insert(b);
    }
    if (n % 2 == 1) {
      return false;
    }
    n = n / 2;
    return h.count(n) == 1;
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