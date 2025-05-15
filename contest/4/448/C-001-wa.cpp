
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
  int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
    map<ll, ll> h;
    ll sum = 0;  // 不删除的时间
    for (int i = 0; i < n; i++) {
      h[position[i]] = time[i];
      if (i > 0) {
        sum += (position[i] - position[i - 1]) * time[i - 1];
      }
    }
    ll ans = sum;
    while (k--) {
      ll p = -1;
      ll saveTime = -__LONG_LONG_MAX__;
      for (auto it = h.begin(); it != h.end(); it++) {
        if (it->first == 0 || it->first == l) {
          continue;
        }

        ll allSaveTime = 0;
        ll dis = next(it)->first - it->first;
        ll oldTime = dis * it->second;
        ll newTime = dis * prev(it)->second;
        allSaveTime += oldTime - newTime;

        if (next(it)->first != l) {
          auto it2 = next(it);

          ll dis2 = next(it2)->first - it2->first;
          ll oldTime2 = dis2 * it2->second;
          ll newTime2 = dis2 * (it2->second + it->second);
          allSaveTime += oldTime2 - newTime2;
        }

        if (allSaveTime >= saveTime) {
          saveTime = allSaveTime;
          p = it->first;
        }
      }
      ans -= saveTime;
      MyPrintf("p=[%lld, %lld], saveTime=%lld, ans=%lld\n", p, h[p], saveTime, ans);
      auto it = h.upper_bound(p);
      it->second += h[p];
      h.erase(p);
    }

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