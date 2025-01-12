
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
class Solution {
  int n;

 public:
  ll countNonDecreasingSubarrays(vector<int>& nums, const int k) {
    n = nums.size();
    vector<int> V(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      V[i] = nums[i - 1];
    }

    vector<ll> preSum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      preSum[i] = preSum[i - 1] + V[i];
    }

    vector<int> nextHeight(n + 1, n + 1);  // 大于等于当前值的下个位置
    vector<pair<ll, int>> sta;
    sta.push_back({INT_MAX, n + 1});
    for (int i = n; i >= 1; i--) {
      const ll v = V[i];
      while (v > sta.back().first) {
        sta.pop_back();
      }
      nextHeight[i] = sta.back().second;
      sta.push_back({v, i});
      // printf("i=%d next=%d\n", i, nextHeight[i]);
    }

    // 滑动窗口
    ll l = 1, r = 1;  //[l, r]
    ll rh = V[r];     // 最大值
    ll rhi = r;       // 最大值下标
    ll sum = 0;       // 使用的次数

    ll ans = 0;
    while (l <= n) {  // 枚举每个左边界
      // 状态转移， l-1 => l
      if (l > 1 && V[l - 1] > V[l]) {
        int lr = nextHeight[l - 1];  // [l, lr-1] 区间内的值都小于 V[l-1]
        bool allCoverFlag = false;
        if (lr > r) {  // 需要全部重新计算
          lr = r + 1;
          allCoverFlag = true;
        }
        ll sumV = preSum[lr - 1] - preSum[l - 1];
        ll sum_l = V[l - 1] * (lr - 1 - l + 1);
        ll sum_k = sum_l - sumV;
        sum -= sum_k;  // 消耗的操作补充回来
        // 正常情况下，R 一定是当前的最大值下标
        // 如果全部覆盖的时候，R 就不是当前最大值的下标了
        ll R = l;
        ll RH = V[R];
        ll RHI = R;
        while (R + 1 < lr) {  // [l, lr) 重新计算
          if (V[R + 1] >= V[R]) {
            R = R + 1;
            RH = V[R];
            RHI = R;
          } else {                            // fast skip, k 肯定够
            int RR = min(nextHeight[R], lr);  // (R, RR) 全部补充到 RH
            ll sumV = preSum[RR - 1] - preSum[R];
            ll sum_l = V[R] * (RR - 1 - R);
            ll sum_k = sum_l - sumV;
            sum += sum_k;  // 由于是滑动窗口前缀转移，肯定够
            if (nextHeight[R] >= lr) {
              break;  // 不更新 RH
            }
            R = RR;
            RH = V[R];
            RHI = R;
          }
        }
        if (allCoverFlag) {
          rh = RH;  // 全部覆盖时，rh 需要按最新的计算
          rhi = RHI;
        }
      }

      // 继续向右移动
      while (r + 1 <= n) {     // 滑动窗口，只会循环一次，复杂度O(n)
        if (V[r + 1] >= rh) {  // 更大
          rh = V[r + 1];
          r = r + 1;
        } else {
          if (rh - V[r + 1] <= k - sum) {  // 不足，需要消耗 k, rh 不变
            sum += rh - V[r + 1];
            r++;
          } else {
            break;  // k 不够了
          }
        }
      }

      // printf("l=%lld r=%lld +%lld sum=%lld\n", l, r, r-l+1, sum);

      ans += r - l + 1;
      l++;
    }
    return ans;
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