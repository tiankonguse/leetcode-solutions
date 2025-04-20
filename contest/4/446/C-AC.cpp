
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
  // k 不大于 5，暴力计算
  int g[6][6];
  int Cal(int x, int pre, int k) {  // 计算 y 使得 (y * x) % k = pre
    for (int y = 0; y < k; y++) {
      if ((y * x) % k == pre) {
        return y;
      }
    }
    return 0;
  }
  void Init(int k) {
    for (int x = 0; x < k; x++) {
      for (int pre = 0; pre < k; pre++) {
        g[x][pre] = Cal(x, pre, k);
      }
    }
  }

  vector<set<int>> numIndexs;
  ll Solver0(vector<int>& nums, int k) {  //
    int n = nums.size();
    int l = 0;
    ll ans = 0;
    while (l < n) {
      if (nums[l] == 0) {
        l++;
        continue;
      }

      int firstTwo = -1;
      auto it21 = numIndexs[2].lower_bound(l);
      if (it21 == numIndexs[2].end()) {
        break;  // 至少需要 1 个 2
      }
      firstTwo = *it21;

      int secondTwo = -1;
      auto it22 = numIndexs[2].lower_bound(firstTwo + 1);
      if (it22 == numIndexs[2].end()) {
        break;  // 至少需要 2 个 2
      }
      secondTwo = *it22;

      int firstZero = n;
      auto it = numIndexs[0].lower_bound(l);
      if (it != numIndexs[0].end()) {
        firstZero = *it;
      }

      if (secondTwo > firstZero) {
        l = firstZero + 1;
        continue;
      }
      ans += (firstZero - secondTwo);
      l++;
    }
    return ans;
  }
  ll Solver2(vector<int>& nums, int k) {  //
    int n = nums.size();
    int l = 0;
    ll ans = 0;
    while (l < n) {
      if (nums[l] == 0) {
        l++;
        continue;
      }
      int firstZero = n;
      auto it = numIndexs[0].lower_bound(l);
      if (it != numIndexs[0].end()) {
        firstZero = *it;
      }

      int firstTwo = -1;
      auto it21 = numIndexs[2].lower_bound(l);
      if (it21 == numIndexs[2].end()) {
        break;  // 至少需要 1 个 2
      }
      firstTwo = *it21;
      if (firstTwo > firstZero) {
        l = firstZero + 1;
        continue;
      }

      int secondTwo = firstZero;
      auto it22 = numIndexs[2].lower_bound(firstTwo + 1);
      if (it22 != numIndexs[2].end()) {
        secondTwo = min(secondTwo, *it22);
      }
      ans += secondTwo - firstTwo;  // 计算 [firstTwo, firstZero) 之间的数
      l++;
    }
    return ans;
  }

 public:
  vector<ll> resultArray(vector<int>& nums, int k) {
    Init(k);
    vector<ll> ans(k, 0);  // 统计子数组乘积模k 等于各下标的个数
    int n = nums.size();
    numIndexs.resize(7);
    for (int i = 0; i < n; i++) {
      nums[i] %= k;
      numIndexs[nums[i]].insert(i);
    }
    // 0 特殊计算
    for (int i = 0; i < n; i++) {
      auto it = numIndexs[0].lower_bound(i);
      if (it == numIndexs[0].end()) {
        break;
      }
      ans[0] += (n - *it);  // i 起始到 [it->first, n-1] 之间的数相乘都是 0
    }
    if (k == 4) {  //  (2 * 2) % 4 = 0
      MyPrintf("pre ans[0]=%lld\n", ans[0]);
      ans[0] += Solver0(nums, k);
      MyPrintf("after ans[0]=%lld\n", ans[0]);
      ans[2] += Solver2(nums, k);
    }

    vector<ll> preMul(6, 0);  // 统计前缀乘积模k
    ll pre = 1;
    preMul[1] = 1;
    for (int x = 1; x < k; x++) {
      // 0 把 nums 拆分为若干个区间，每个区间独立计算
      fill(preMul.begin(), preMul.end(), 0);
      preMul[1] = 1;
      pre = 1;
      if (k != 4) {
        int l = 0, r = 0;
        while (r < n) {
          if (nums[r] == 0) {
            r++;
            l = r;
            fill(preMul.begin(), preMul.end(), 0);
            preMul[1] = 1;
            pre = 1;
            continue;
          }
          pre = (pre * nums[r]) % k;
          int y = g[x][pre];  // (y * x ) % k = pre
          // MyPrintf("[%d,%d] x=%d pre=%lld y=%d preMul[y]=%lld\n", l, r, x, pre, y, preMul[y]);
          ans[x] += preMul[y];
          preMul[pre]++;
          r++;
        }
      } else {                 // 4 非质数，需要特殊处理
        if (x == 2) continue;  // 已经特殊计算
        int l = 0, r = 0;
        while (r < n) {
          if (nums[r] == 0 || nums[r] == 2) {
            r++;
            l = r;
            fill(preMul.begin(), preMul.end(), 0);
            preMul[1] = 1;
            pre = 1;
            continue;
          }
          pre = (pre * nums[r]) % k;
          int y = g[x][pre];  // (y * x ) % k = pre
          // MyPrintf("[%d,%d] x=%d pre=%lld y=%d preMul[y]=%lld\n", l, r, x, pre, y, preMul[y]);
          ans[x] += preMul[y];
          preMul[pre]++;
          r++;
        }
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