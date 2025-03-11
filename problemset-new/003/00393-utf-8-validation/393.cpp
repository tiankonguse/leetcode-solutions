
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
  bool validUtf8(vector<int>& data) {
    int n = data.size();
    int bytesToProcess = 0;
    for (int v : data) {
      if (bytesToProcess == 0) {
        if ((v >> 5) == 0b110) {
          bytesToProcess = 1;
        } else if ((v >> 4) == 0b1110) {
          bytesToProcess = 2;
        } else if ((v >> 3) == 0b11110) {
          bytesToProcess = 3;
        } else if ((v >> 7)) {
          return false;
        } else {
          // 0b0xxxxxxx
          continue;
        }
      } else {
        if ((v >> 6) != 0b10) {
          return false;
        }
        bytesToProcess--;
      }
    }
    return bytesToProcess == 0;
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