
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
  int findSpecialInteger(vector<int>& arr) {
    int n = arr.size();
    int threshold = n / 4;
    for (int i = threshold; i < n; i += threshold) {
      int v = arr[i];
      int l = lower_bound(arr.begin(), arr.begin() + i, v) - arr.begin();
      int r = upper_bound(arr.begin() + i + 1, arr.end(), v) - arr.begin();
      if (r - l > threshold) {
        return v;
      }
    }
    return -1;
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