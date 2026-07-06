
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
  long long getSum(vector<int>& nums) {
    int n = nums.size();
    int nn = n * 2 + 2;
    vector<ll> ss(nn, 0);
    vector<ll> sum(nn, 0);  // sum[i] 以 i 为中心，p[i] 为半径的子串和
    vector<ll> p(nn, 0);
    for (int i = 0; i < n; i++) {
      ss[i * 2 + 1] = 0;
      ss[i * 2 + 2] = nums[i];
    }
    vector<ll> preSum(nn, 0);
    for (int i = 1; i < nn; i++) {
      preSum[i] = preSum[i - 1] + ss[i];
    }

    ll ans = 0;
    int r = 0, id = 0;  // 到达最远 r 时，中心为 id, (id-r, id+r)
    for (int i = 1; i < nn; i++) {
      p[i] = 1;
      sum[i] = ss[i];
      if (r > i) {
        p[i] = min(p[2 * id - i], ll(r - i));
        int ll = i - p[i] + 1, rr = i + p[i] - 1;  // [ll, rr]
        if (ll == 0) {
          sum[i] = preSum[rr];
        } else {
          sum[i] = preSum[rr] - preSum[ll - 1];
        }
      }
      while (i + p[i] < nn && i - p[i] > 0 && ss[i + p[i]] == ss[i - p[i]]) {
        sum[i] += ss[i + p[i]] + ss[i - p[i]];
        p[i]++;
      }
      ans = max(ans, sum[i]);
      if (i + p[i] > r) {
        r = i + p[i];
        id = i;
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