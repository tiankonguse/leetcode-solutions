
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
  int superPow(int a, vector<int>& b) {
    const ll mod = 1337;
    std::reverse(b.begin(), b.end());
    ll base = a % mod;
    ll ans = 1;
    for (auto v : b) {
      ll nextBase = 1;
      for (int i = 0; i < 10; i++) {
        if (i == v) {
          ans = (ans * nextBase) % mod;
        }
        nextBase = (nextBase * base) % mod;
      }
      base = nextBase;
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(int a, const vector<int>& nums, const int& ans) {
  TEST_SMP2(Solution, superPow, ans, a, nums);
}

int main() {
  for (int i = 1; i < 10; i++) {
    Test(2, {i}, (1L << i) % 1337);
  }
  for (int i = 10; i < 32; i++) {
    Test(2, {i / 10, i % 10}, (1L << i) % 1337);
  }
  Test(2, {1, 0}, 1024);
  Test(1, {4, 3, 3, 8, 5, 2}, 1);
  Test(2147483647, {2, 0, 0}, 1198);
  return 0;
}

#endif