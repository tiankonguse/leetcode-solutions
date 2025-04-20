
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

 public:
  vector<ll> resultArray(vector<int>& nums, int k) {
    Init(k);
    vector<ll> ans(k, 0);  // 统计子数组乘积模k 等于各下标的个数
    int n = nums.size();
    map<int, int> zeroIndex;
    for (int i = 0; i < n; i++) {
      nums[i] %= k;
      if (nums[i] == 0) {
        zeroIndex[i] = 1;
      }
    }
    // 0 特殊计算
    for (int i = 0; i < n; i++) {
      auto it = zeroIndex.lower_bound(i);
      if (it == zeroIndex.end()) {
        break;
      }
      ans[0] += (n - it->first);  // i 起始到 [it->first, n-1] 之间的数相乘都是 0
    }
    vector<ll> preMul(k, 0);  // 统计前缀乘积模k
    for (int x = 0; x < k; x++) {
      // 0 把 nums 拆分为若干个区间，每个区间独立计算
      int l = 0, r = 0;
      while (l < n) {  // [l, r) 是一个非 0 区间
        if (nums[l] == 0) {
          l++;
          continue;
        }
        auto it = zeroIndex.lower_bound(l);
        if (it == zeroIndex.end()) {  // 没有0
          r = n;
        } else {
          r = it->first;
        }
        preMul.clear();
        preMul.resize(k, 0);
        preMul[1] = 1;
        ll pre = 1;
        for (int j = l; j < r; j++) {  // 计算 [l, j] 区间
          pre = (pre * nums[j]) % k;
          // (y * x ) % k = pre
          int y = g[x][pre];
          ans[x] += preMul[y];
          preMul[pre]++;
        }
        l = r + 1;
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