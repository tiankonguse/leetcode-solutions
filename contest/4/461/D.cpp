
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
constexpr ll INFL = 1LL << 60;
class Solution {
 public:
  long long maxSumTrionic(vector<int>& nums) {
    int n = nums.size();
    // 第一步：计算出有序性的分割线
    vector<int> nodes;
    nodes.reserve(n);
    int dir = 0;  // 0: 未知, 1: 上升, -1: 下降
    nodes.push_back(0);
    for (int i = 1; i < n; i++) {
      int newDir = 0;
      if (nums[i - 1] < nums[i]) {
        newDir = 1;
      } else if (nums[i - 1] > nums[i]) {
        newDir = -1;
      } else {
        newDir = 0;
      }

      if (dir != 0 && dir == newDir) {
        nodes.pop_back();
      }

      nodes.push_back(i);  // 相等的情况,当做分割线
      dir = newDir;
    }
    ll ans = -INFL;
    const int m = nodes.size();
    for (int i = 0; i + 3 < m; i++) {
      const int l = nodes[i];
      const int p = nodes[i + 1];  // 上升的结束点
      const int q = nodes[i + 2];  // 下降的结束点
      const int r = nodes[i + 3];  // 上升的结束点
      if (nums[l] < nums[p] && nums[p] > nums[q] && nums[q] < nums[r]) {
        // 计算三段的和
        ll sum = 0;

        ll tmp1 = nums[p - 1];
        ll sum1 = tmp1;
        for (int j = p - 2; j >= l; j--) {
          tmp1 += nums[j];
          sum1 = max(sum1, tmp1);
        }

        ll sum2 = 0;
        for (int j = p; j <= q; j++) {
          sum2 += nums[j];
        }

        ll tmp3 = nums[q + 1];
        ll sum3 = tmp3;
        for (int j = q + 2; j <= r; j++) {
          tmp3 += nums[j];
          sum3 = max(sum3, tmp3);
        }
        ans = max(ans, sum1 + sum2 + sum3);
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