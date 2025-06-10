
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
  bool canMakeEqual(vector<int>& nums, int k) {
    int n = nums.size();
    if (n == 1) return true;
    auto Check = [&](int V) {
      int cnt = 0;
      int flag = 0;
      for (auto v : nums) {
        if (flag) {
          v = -v;
          flag = 0;
        }
        if (v == V) continue;
        flag = 1;
        cnt++;
      }
      if (cnt > k) return false;
      return flag == 0;
    };
    return Check(1) || Check(-1);
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