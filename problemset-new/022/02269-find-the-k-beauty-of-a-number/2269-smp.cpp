
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
  int divisorSubstrings(const int num, const int k) {
    string s = to_string(num);
    int n = s.size();
    if (n < k) return 0;  // 不存在长度为 k 的子串
    int ans = 0;
    int v = 0;
    const int p = pow(10, k - 1);
    MyPrintf("p=%d\n", p);
    for (int i = 0; i < n; i++) {
      v = v * 10 + s[i] - '0';
      if (i < k - 1) continue;
      if (v > 0 && num % v == 0) ans++;
      v -= (s[i - k + 1] - '0') * p;
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