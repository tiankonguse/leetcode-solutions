
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
const ll V = 1e6;
class Solution {
 public:
  ll maxScore(const vector<int>& points, const ll m) {
    const int n = points.size();
    vector<ll> nums(n, 0);
    vector<ll> uses(n, 0);
    vector<ll> adds(n, 0);
    auto Check = [&](ll minVal) -> bool {
      if (minVal == 0) return true;

      ll sum = 0;
      for (int i = 0; i < n; i++) {
        ll v = points[i];
        nums[i] = (minVal + v - 1) / v;  // 至少需要到达多少次，才能不小于最小值
        uses[i] = 0;
        adds[i] = 0;

        sum += nums[i];
        if (sum > m) return false;
      }
      ll addNum = 0;

      // 优先贪心计算，在 n-1 结束，需要多少次操作
      for (int i = 0; i < n; i++) {
        if (i + 1 < n) {  // 不是最后一个, 由于后面还有非0，所以前面需要加一往后移动一次
          ll now = adds[i] + nums[i];
          ll left = now - uses[i];

          if (left > nums[i + 1]) {
            adds[i + 1] += left - nums[i + 1];
            addNum += left - nums[i + 1];
          }
          uses[i + 1] += left - 1;  // 大于 1 时，来回移动
        } else {                    // 最后一位
          ll now = adds[i] + nums[i];
          ll left = now - uses[i];
          if (left > 1) {  // 与左边的来回移动
            adds[i - 1] += left - 1;
            addNum += left - 1;
          }
        }
      }
      for (int i = n - 1; i > 0; i--) {
        if (adds[i] > 0) {
          adds[i]--;
          addNum--;
        } else {
          break;
        }
      }
      if (sum + addNum > m) return false;
      return true;
    };

    ll l = 0, r = V * m;  // 只有2个，来回跑，最大值为 V*(m+1)/2
    while (l < r) {       // [l, r)
      ll mid = (l + r) / 2;
      if (Check(mid)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return r - 1;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif