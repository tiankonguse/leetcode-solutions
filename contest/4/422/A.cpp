
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
  bool isBalanced(const string& num) {
    vector<ll> sums(2, 0);
    int n = num.size();
    for (int i = 0; i < n; i++) {
      sums[i % 2] += (num[i] - '0');
    }
    return sums[0] == sums[1];
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const string& num, const bool& ans) {
  TEST_SMP1(Solution, isBalanced, ans, num);
}

int main() {
  Test("1234", false);
  Test("24123", true);
  return 0;
}

#endif