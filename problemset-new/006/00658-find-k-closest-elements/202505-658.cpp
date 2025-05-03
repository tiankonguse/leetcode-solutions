
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
  vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int n = arr.size();
    int p = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
    if (p == n) {
      p--;  // 保证 p 有效
    }

    if (p > 0 && abs(arr[p - 1] - x) <= abs(arr[p] - x)) {
      p--;  // 有可能小于 x 的距离更近
    }
    int l = p, r = p;
    while (r - l + 1 < k) {
      if (l == 0) {
        r++;
      } else if (r == n - 1) {
        l--;
      } else {
        if (abs(arr[l - 1] - x) <= abs(arr[r + 1] - x)) {
          l--;
        } else {
          r++;
        }
      }
    }
    return vector<int>(arr.begin() + l, arr.begin() + r + 1);
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