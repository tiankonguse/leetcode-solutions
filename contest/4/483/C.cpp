
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  ll minimumCost(string s, string t, ll flipCost, ll swapCost, ll crossCost) {
    ll v01 = 0, v10 = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
      if (s[i] != t[i]) {
        if (s[i] == '0') {
          v01++;
        } else {
          v10++;
        }
      }
    }
    if (v01 < v10) {
      swap(v01, v10);
    }
    MyPrintf("v01=%lld, v10=%lld\n", v01, v10);
    ll ans = 0;
    // op1: flip one, fix one
    // op2: swap two, fix two
    // op3: cross one and swap two, fix two
    ll op1 = flipCost * 2;
    ll op2 = swapCost;
    ll op3 = crossCost + swapCost;
    if (op2 <= op1) {
      ll v = min(v01, v10);
      ans += v * op2;
      v01 -= v;
      v10 -= v;
      MyPrintf("after op2: v01=%lld, v10=%lld, ans=%lld\n", v01, v10, ans);
    }
    if (op3 <= op1 && v01 >= 2) {
      ll v = v01 / 2;
      ans += v * op3;
      v01 -= v * 2;
      MyPrintf("after op3: v01=%lld, v10=%lld, ans=%lld\n", v01, v10, ans);
    }
    ans += (v01 + v10) * flipCost;
    MyPrintf("final: v01=%lld, v10=%lld, ans=%lld\n", v01, v10, ans);
    return ans;
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