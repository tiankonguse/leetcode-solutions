
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
  long long maxTotal(vector<int>& value, vector<int>& limit) {
    int n = value.size();
    vector<pair<ll, ll>> nums;
    nums.reserve(n);
    for (int i = 0; i < n; i++) {
      nums.push_back({limit[i], value[i]});
    }
    sort(nums.begin(), nums.end(), [](auto& a, auto& b) {  //
      auto [la, va] = a;
      auto [lb, vb] = b;
      if (la != lb) {
        return la < lb;
      } else {
        return va > vb;
      }
    });

    ll ans = 0;
    int x = 0;
    int maxX = 0;
    queue<ll> que;
    for (auto [la, va] : nums) {
      if (x < la && maxX < la) {  
        ans += va;
        que.push(la);
        x++;
        maxX = max(maxX, x);
        while (!que.empty() && que.front() <= x) {
          que.pop();
        }
        x = que.size();
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