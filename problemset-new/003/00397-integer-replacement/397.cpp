
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
/*
// 01 -> 0

// 011 -> 100 -> 10 -> 1 -> 0
// 011 -> 10 -> 1

// 111 -> 1000 -> 100 -> 10 -> 1
// 111 -> 110 ->  11   -> 10 -> 1

// 1111 -> 10000 -> 1000 -> 100 -> 10 -> 1
// 1111 ->  1110 -> 111  -> 110 -> 11 -> 10 -> 1

// 1001 -> 1000 -> 100 -> 10 -> 1
// 1001 -> 1010 -> 101 -> 110 -> 11 -> 10 -> 1

// 101 -> 100 -> 10  -> 1 -> 0
// 101 -> 110 -> 11 -> 10 -> 1

// 1011 -> 1010 -> 101 -> 100 -> 10 -> 1
// 1011 -> 1100 -> 110 -> 11 -> 10 -> 1

// 11011 -> 11010 -> 1101 -> 1100 -> 110 -> 11 -> 10 -> 1
// 11011 -> 11100 -> 1110 -> 111  -> 110 -> 11 -> 10 -> 1

// 111011 -> 111010 -> 11101 -> 11100 -> 1110 -> 111  -> 110 -> 11 -> 10 -> 1
// 111011 -> 111100 -> 11110 -> 1111  -> 1110 -> 110  -> 11  -> 10 -> 1

*/
class Solution {
 public:
  int integerReplacement(ll n) {
    int ans = 0;
    while (n != 1) {
      printf("%b %d\n", n, n);
      if ((n & 1) == 0) {
        n >>= 1;
        ++ans;
      } else if ((n & 0b11) == 0b01) {  // 01
        n -= 1;
        ++ans;
      } else if ((n & 0b1111) == 0b11) {  // 0011
        n -= 1;
        ++ans;
      } else {
        n += 1;
        ++ans;
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