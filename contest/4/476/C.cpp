
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
  vector<ll> base9;

 public:
  long long countDistinct(long long n) {
    string s = to_string(n);
    int len = s.length();
    base9.push_back(1);  // 9^0
    ll ans = 0;
    for (int i = 1; i < len; i++) {
      base9.push_back(base9.back() * 9);  // 9^i
      ans += base9.back();
    }
    int i;
    for (i = 0; i < len; i++) {
      int digit = s[i] - '0';
      for (int j = 1; j < digit; j++) {
        int leftLen = len - i - 1;
        ans += base9[leftLen];
      }
      if (digit == 0) {
        break;
      }
    }
    if (i == len) ans++;
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