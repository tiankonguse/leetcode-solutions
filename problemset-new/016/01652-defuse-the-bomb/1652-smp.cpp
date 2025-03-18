
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
  vector<int> decrypt(vector<int>& code, int k) {
    int n = code.size();
    vector<int> ans(n, 0);
    if (k == 0) return ans;
    int flag = 0;
    if (k < 0) {
      flag = 1;
      reverse(code.begin(), code.end());
      k = -k;
    }
    int sum = 0;
    for (int i = 0; i < n + k; i++) {
      sum += code[i % n];
      if (i < k - 1) {
        continue;
      }
      ans[(i - k + n) % n] = sum;
      sum -= code[(i - k + 1 + n) % n];
    }
    if (flag) {
      reverse(ans.begin(), ans.end());
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