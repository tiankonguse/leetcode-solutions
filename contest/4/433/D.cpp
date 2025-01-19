
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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod1e7 = 1000000007;
constexpr ll INFL = 1LL << 60;

class Solution {
  ll Cal(vector<int>& nums, const int k) {
    int n = nums.size();
    vector<int> left(n + 2, 0);
    vector<int> right(n + 2, n + 1);

    // 定义：相等时，右边的更大
    // 先计算左边界
    vector<pair<ll, int>> h;
    h.push_back({INT_MAX, 0});
    for (int i = 1; i <= n; i++) {
      const ll v = nums[i - 1];
      const pair<ll, int> p = {v, i};

      ll l = 0, r = h.size();  // [l, r)
      while (l < r) {
        int mid = (l + r) / 2;
        if (h[mid] > p) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }  // 大于自己的
      r--;
      left[i] = h[r].second + 1;
      while (h.back() <= p) {
        h.pop_back();
      }
      h.push_back(p);
    }

    // 计算右边界
    h.clear();
    h.push_back({INT_MAX, n + 1});
    for (int i = n; i >= 1; i--) {
      const ll v = nums[i - 1];
      const pair<ll, int> p = {v, i};
      ll l = 0, r = h.size();
      while (l < r) {  // [l, r)
        int mid = (l + r) / 2;
        if (h[mid] > p) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      r--;
      right[i] = h[r].second - 1;
      while (h.back() <= p) {
        h.pop_back();
      }
      h.push_back(p);
    }

    ll ans = 0;
    // 计算最大值
    for (int i = 1; i <= n; i++) {
      ll v = nums[i - 1];
      ll leftNum = min(i - left[i], k - 1);
      ll rightNum = min(right[i] - i, k - 1);
      ll num = 0;
      if (leftNum + rightNum + 1 <= k) {  // 任意选择
        num = (1 + leftNum) * (1 + rightNum);
      } else if (leftNum >= k - 1 && rightNum >= k - 1) {
        num = (1 + k) * k / 2;
      } else {  // (k, 2*k-1)
        ll x = k - (rightNum + 1);
        num += (1 + x) * (1 + rightNum);  // 左侧 [0,x]， 右侧 [0~rightNum]

        ll R = (rightNum - 1) + 1;
        ll L = (k - 1 - leftNum) + 1;
        num += (L + R) * (R - L + 1) / 2;
      }

      ans += v * num;
    }

    // printf("ans=%lld\n", ans);
    return ans;
  }

 public:
  long long minMaxSubarraySum(vector<int>& nums, const int k) {
    ll ans = 0;
    ans += Cal(nums, k);
    for (auto& v : nums) {
      v = -v;
    }
    ans -= Cal(nums, k);
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  // Test({1, 2, 3}, 3);
  return 0;
}

#endif