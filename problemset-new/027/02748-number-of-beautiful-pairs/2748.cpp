
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

typedef long long ll;
class Solution {
 public:
  int countBeautifulPairs(const vector<int>& nums) {
    int n = nums.size();
    vector<int> cnt(10, 0);
    int ans = 0;
    for (auto v : nums) {
      int first = 0, last = v % 10;
      while (v) {
        first = v % 10;
        v /= 10;
      }
      for (int i = 1; i <= 9; i++) {
        if (gcd(i, last) == 1) {
          ans += cnt[i];
        }
      }
      cnt[first]++;
    }
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