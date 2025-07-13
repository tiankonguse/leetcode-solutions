
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
  char processStr(const string& s, long long k) {
    int n = s.size();
    vector<ll> nums(n + 1, 0);
    ll len = 0;
    nums[0] = 0;
    // string ans;
    for (int i = 1; i <= n; i++) {
      char c = s[i - 1];
      if ('a' <= c && c <= 'z') {
        // ans.push_back(c);
        len++;
      } else if (c == '*') {
        if (len > 0) {
          len--;
        }
        // if (!ans.empty()) {
        //   ans.pop_back();
        // }
      } else if (c == '#') {
        // ans += ans;
        len += len;
      } else if (c == '%') {
        // reverse(ans.begin(), ans.end());
        // do nothing
      }
      // MyPrintf("i: %d, c: %c, ans: %s, len: %lld\n", i, c, ans.c_str(), len);
      nums[i] = len;
    }
    // MyPrintf("k=%lld ans[k]: %c\n", k, ans[k]);
    MyPrintf("k=%lld \n", k);
    if (k >= len) return '.';
    for (int i = n; i >= 1; i--) {  //
      ll oldK = k;
      ll l = nums[i];
      char c = s[i - 1];
      if ('a' <= c && c <= 'z') {
        if (k == l - 1) {
          return c;
        }
      } else if (c == '*') {
        // do nothing
      } else if (c == '#') {
        ll l2 = l / 2;
        if (k >= l2) {
          k -= l2;
        }
      } else if (c == '%') {
        k = l - 1 - k;  // 翻转
      }
      MyPrintf("i: %d, c: %c, l=%lld oldK=%lld k=%lld\n", i, c, l, oldK, k);
    }
    return '.';
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