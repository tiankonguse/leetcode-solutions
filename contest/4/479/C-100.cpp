
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
  ll totalScore(ll hp, vector<int>& damage, vector<int>& requirement) {
    int n = damage.size();
    vector<ll> leftHp(n + 1);
    leftHp[n] = hp;
    for (int i = n - 1; i >= 0; i--) {
      ll d = damage[i];
      leftHp[i] = leftHp[i + 1] - d;
    }
    for (int i = 0; i < n; i++) {
      MyPrintf("i=%d, leftHp=%lld\n", i, leftHp[i]);
    }
    ll ans = 0;
    ll r = 0;
    leftHp.pop_back();
    for (int i = n - 1; i >= 0; i--) {
      ll d = damage[i];
      ll v = requirement[i] - r;
      // 查询大于等于 r 的个数
      ll cnt = leftHp.end() - lower_bound(leftHp.begin(), leftHp.end(), v);
      MyPrintf("i=%d, cnt=%lld, d=%lld v=%lld\n", i, cnt, d, v);
      ans += cnt;
      r += d;
      leftHp.pop_back();
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