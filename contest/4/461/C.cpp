
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
  int minTime(const string& s, const vector<int>& order, const int k) {
    const int n = s.size();
    ll ans = 0;
    set<int> S;
    for (int t = 0; t < n; t++) {
      const int i = order[t];
      auto it = S.lower_bound(i);  // 不存在相等值
      ll w = n - i;
      if (it != S.end()) {
        w = *it - i;
      }
      ll h = i + 1;
      if (it != S.begin()) {
        --it;
        h = i - *it;
      }
      ans += w * h;
      if (ans >= k) {
        return t;
      }
      S.insert(i);
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