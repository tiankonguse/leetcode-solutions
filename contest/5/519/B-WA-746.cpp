
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 746 / 806 个通过的测试用例

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;

set<ll> oddMp, evenMp;
ll mods[7] = {1, ll(1e1), ll(1e2), ll(1e3), ll(1e4), ll(1e5), ll(1e6)};
ll Reverse(ll v) {
  ll V = 0;
  while (v) {
    V = V * 10 + v % 10;
    v /= 10;
  }
  return V;
}
int isInit = false;
void Init() {
  if (isInit) return;
  isInit = true;
  for (int w = 1; w <= 8; w++) {
    ll half = (w + 1) / 2;
    for (ll i = mods[half - 1]; i < mods[half]; i++) {
      ll ri = Reverse(i);
      ll v = 0;
      if (w % 2 == 0) {
        v = i * mods[half] + ri;
      } else {
        v = i * mods[half - 1] + (ri % mods[half - 1]);
      }
      if (v % 2 == 0) {
        evenMp.insert(v);
      } else {
        oddMp.insert(v);
      }
    }
  }
}
class Solution {
  ll Solver(ll v, const set<ll>& mp) {
    auto it = mp.lower_bound(v);
    if (it == mp.end()) {
      it--;
      return (*it - v) / 2;
    }
    if (*it == v) {
      return 0;
    }
    ll up = *it;
    it--;
    ll down = *it;
    return min((up - v) / 2, (v - down) / 2);
  }

 public:
  ll minOperations(vector<int>& nums) {
    Init();
    ll ans = 0;
    for (ll v : nums) {
      if (v % 2 == 0) {
        ans += Solver(v, evenMp);
      } else {
        ans += Solver(v, oddMp);
      }
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