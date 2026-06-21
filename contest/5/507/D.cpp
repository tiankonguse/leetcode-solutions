
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

const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
class Solution {
  ll CalCnt(ll val, ll dec, ll threshold) {
    // val 每次减少 dec，直到小于等于 threshold
    return max(0LL, (val - threshold + dec - 1) / dec);
  }

 public:
  int maxTotalValue(vector<int>& value, vector<int>& decay, int m) {  //
    int n = value.size();
    vector<pair<ll, ll>> nums(n);
    for (int i = 0; i < n; i++) {
      nums[i] = {value[i], decay[i]};
    }
    ll ans = 0;
    while (m > max4 && nums.size() > 0) {
      ll maxVal = nums.front().first;
      for (auto& [val, dec] : nums) {
        maxVal = max(maxVal, val);
      }
      ll left = 0, right = maxVal + 1;  // [left, right)
      while (left < right) {
        ll mid = (left + right) / 2;
        ll cnt = 0;
        for (auto& [val, dec] : nums) {
          cnt += CalCnt(val, dec, mid);
        }
        if (cnt <= m) {
          right = mid;
        } else {
          left = mid + 1;
        }
      }
      ll threshold = left;
      for (auto& [val, dec] : nums) {
        ll cnt = CalCnt(val, dec, threshold);
        if (cnt == 0) continue;
        ans += cnt * (val + val - (cnt - 1) * dec) / 2;
        ans %= mod;
        m -= cnt;
        val -= cnt * dec;
      }
      // nums 中删除 value <= 0 的元素, O(1) 删除算法
      n = nums.size();
      for (int i = 0; i < n; i++) {
        if (nums[i].first <= 0) {
          swap(nums[i], nums[--n]);
          i--;
        }
      }
      nums.resize(n);
    }

    // 最后一批大于 max4，直接优先队列计算
    priority_queue<pair<ll, ll>> pq;
    for (auto& [val, dec] : nums) {
      pq.push({val, dec});
    }
    while (m > 0 && !pq.empty()) {  // 每次减少一个
      auto [val, dec] = pq.top();
      pq.pop();

      ans += val;
      ans %= mod;

      val -= dec;
      if (val > 0) pq.push({val, dec});
      m--;
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