
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
// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; (t = x % y); x = y, y = t);
  return y;
}
class Solution {
 public:
  int maxLength(vector<int>& nums) {
    // 任何两个数字都互质，不存在公约数
    int n = nums.size();

    auto Check = [&n, &nums](int l, int r) {
      for (int i = l; i < r; i++) {
        if (Gcd(nums[i], nums[r]) > 1) return false;
      }
      return true;
    };

    int ans = 2;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {  // 如果 j 和 [i,j-1] 都互质，则 [i,j]是答案
        if (Check(i, j)) {
          ans = max(ans, j - i + 1);
        } else {
          break;
        }
      }
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