
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
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  ll Solver(ll v, ll ans) {
    if (v <= ans) {
      return ans - v;
    }
    for (int b = 31; b >= 0; b--) {
      if ((ans & (1LL << b)) == 0) {
        continue;
      }
      ll mask = (1LL << (b + 1)) - 1;
      ll v2 = v & mask;
      ll ans2 = ans & mask;
      if (ans2 >= v2) {
        return ans2 - v2;
      }
    }
    return 0;
  }
  int maximumAND(vector<int>& nums, int k, int m) {
    ll ans = 0;
    max_queue<ll> que;  
    for (int b = 30; b >= 0; b--) {
      ans |= (1LL << b);
      while (!que.empty()) que.pop();
      ll cost = 0;
      for (ll v : nums) {
        ll x = Solver(v, ans);
        cost += x;
        que.push(x);
        if (que.size() > m) {
          cost -= que.top();
          que.pop();
        }
      }
      if (cost > k) {
        ans ^= (1LL << b);
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