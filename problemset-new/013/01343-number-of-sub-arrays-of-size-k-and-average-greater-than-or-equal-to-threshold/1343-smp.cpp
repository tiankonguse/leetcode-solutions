
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
  int numOfSubarrays(vector<int>& arr, int k, int threshold) {
    ll sum = 0;
    int cnt = 0;
    ll target = k * threshold;
    int n = arr.size();
    for (int i = 0; i < n; i++) {
      sum += arr[i];
      if (i < k - 1) {
        continue;
      }
      if (sum >= target) {
        cnt++;
      }
      sum -= arr[i - k + 1];
    }
    return cnt;
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