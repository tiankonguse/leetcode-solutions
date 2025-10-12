
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
  int sumDivisibleByK(vector<int>& nums, int k) {
    vector<int> count(111, 0);
    for (int num : nums) {
      count[num]++;
    }
    int sum = 0;
    for (int i = 0; i < 111; i++) {
      int c = count[i];
      if (c % k == 0) {
        sum += c * i;
      }
    }
    return sum;
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