
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
  int countGroups(vector<int>& position, vector<int>& speed, int D) {
    int n = position.size();
    vector<pair<ll, ll>> sta1;
    sta1.reserve(n);
    for (int i = 0; i < n; i++) {
      const ll p = position[i];
      const ll s = speed[i];
      if (!sta1.empty()) {
        MyPrintf("Check1: <%lld %lld> <%lld %lld>,max=%lld\n", sta1.back().first, sta1.back().second, p, s,
                 sta1.back().first + D);
      }
      while (!sta1.empty() && sta1.back().first + D >= p) {
        MyPrintf("Merge1: <%lld %lld> <%lld %lld>\n", sta1.back().first, sta1.back().second, p, s);
        sta1.pop_back();
      }
      MyPrintf("Push1: <%lld %lld>\n", p, s);
      sta1.push_back({p, s});
    }

    vector<pair<ll, ll>> sta2;
    sta2.reserve(n);
    for (const auto [p, s] : sta1) {
      while (!sta2.empty() && sta2.back().second > s) {
        MyPrintf("Merge2: <%lld %lld> <%lld %lld>\n", sta2.back().first, sta2.back().second, p, s);
        sta2.pop_back();
      }
      MyPrintf("Push2: <%lld %lld>\n", p, s);
      sta2.push_back({p, s});
    }

    return sta2.size();
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