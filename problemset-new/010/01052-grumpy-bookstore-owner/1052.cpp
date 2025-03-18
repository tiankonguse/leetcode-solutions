
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
  int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
    int n = customers.size();
    int satisfied = 0;
    for (int i = 0; i < n; i++) {
      if (grumpy[i] == 0) {
        satisfied += customers[i];
      }
    }
    int maxChangeSatisfied = 0;
    int sum = 0;
    for (int r = 0; r < n; r++) {
      int l = r - minutes + 1;
      if (grumpy[r]) {
        sum += customers[r];
      }
      if (l < 0) {
        continue;
      }
      maxChangeSatisfied = max(maxChangeSatisfied, sum);
      if (grumpy[l]) {
        sum -= customers[l];
      }
    }
    return satisfied + maxChangeSatisfied;
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