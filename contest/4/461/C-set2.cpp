
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
    int n = s.size();
    int l = 0, r = n;
    set<int> S;
    auto Check = [&](const int mid) -> bool {
      S.clear();
      for (int i = 0; i <= mid; i++) {
        S.insert(order[i]);
      }
      ll ans = 0;
      for (int i = 0; i < n; i++) {
        auto it = S.lower_bound(i);
        if (it != S.end()) {
          ans += n - *it;
        }
      }
      return ans >= k;
    };
    while (l < r) {
      int mid = (l + r) / 2;
      if (Check(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    if (l == n) return -1;
    return l;
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