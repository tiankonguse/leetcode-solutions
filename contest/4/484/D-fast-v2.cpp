
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
    ll ab = (v ^ ans) & ans;  // 最高位 1 就是分界线
    if(ab == 0){
      return 0;
    }
    int b = 32 - __builtin_clz(ab);
    ll mask = (1LL << b) - 1;
    return (ans & mask) - (v & mask);
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