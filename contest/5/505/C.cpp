
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
const ll kMinVal = -(ll)4e15;

class Solution {
 public:
  long long maximumSum(vector<int>& nums, int m, int l, int r) {  //
    int n = nums.size();

    vector<ll> pre(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      pre[i] = pre[i - 1] + nums[i - 1];
    }

    vector<ll> prev(n + 1, kMinVal);
    vector<ll> cur(n + 1, kMinVal);

    prev[0] = 0;
    for (int i = 1; i <= n; i++) {
      prev[i] = 0;  // 选 0 个区间
    }

    ll ans = kMinVal;
    for (int k = 1; k <= m; k++) {
      fill(cur.begin(), cur.end(), kMinVal);

      deque<int> dq;

      for (int i = l; i <= n; i++) {
        int add = i - l;
        if (add >= 0) {
          ll v = prev[add] - pre[add];
          while (!dq.empty() && prev[dq.back()] - pre[dq.back()] <= v) dq.pop_back();
          dq.push_back(add);
        }

        int left = i - r;
        while (!dq.empty() && dq.front() < left) dq.pop_front();

        cur[i] = cur[i - 1];

        if (!dq.empty()) {
          cur[i] = max(cur[i], pre[i] + (prev[dq.front()] - pre[dq.front()]));
        }
      }

      ans = max(ans, cur[n]);
      swap(prev, cur);
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