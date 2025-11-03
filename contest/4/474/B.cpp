
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
using min_queue = priority_queue<T, vector<T>, greater<T>>;
class Solution {
 public:
  long long maxProduct(vector<int>& nums) {
    const ll maxVal = 1e5;
    min_queue<ll> que; // 大小为 2 的最小堆
    for (ll v : nums) {
      v = abs(v);
      que.push(v);
      if (que.size() > 2) {
        que.pop();
      }
    }
    ll a = abs(que.top());
    que.pop();
    ll b = abs(que.top());
    que.pop();
    return a * b * maxVal;
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