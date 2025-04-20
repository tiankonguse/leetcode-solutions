
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
  vector<ll> resultArray(vector<int>& nums, int k) {
    vector<ll> ans(k, 0);  // 统计子数组乘积模k 等于各下标的个数
    int n = nums.size();
    vector<ll> pre(k, 0);
    for (auto v : nums) {
      vector<ll> tmp(k, 0);
      v %= k;
      tmp[v % k] = 1;  // 单独一个数
      for (int i = 0; i < k; i++) {
        tmp[(i * v) % k] += pre[i];
      }
      pre = tmp;
      for (int i = 0; i < k; i++) {
        ans[i] += pre[i];
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