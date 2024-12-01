
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
  int smallestNumber(int n) {
    for (int i = 0; n >= (1 << i); i++) {
      n = n | (1 << i);
    }
    return n;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const int n, const int& ans) {
  TEST_SMP1(Solution, smallestNumber, ans, n);
}

int main() {
  Test(1, 1);
  Test(2, 3);
  Test(3, 3);
  Test(4, 7);
  Test(5, 7);
  Test(6, 7);
  Test(7, 7);
  Test(10, 15);
  return 0;
}

#endif