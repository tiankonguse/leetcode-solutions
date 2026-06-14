
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
const ll kMinVal = -1e18;
struct segtree {
  int n;
  std::vector<std::pair<ll, ll>> vals;
  segtree(int n) : n(n) { vals.assign(n << 1, {kMinVal, kMinVal}); }
  void set(int i, std::pair<ll, ll> x) {
    for (vals[i += n] = x; i > 1; i >>= 1) {
      vals[i >> 1] = std::max(vals[i], vals[i ^ 1]);
    }
  }
  std::pair<ll, ll> prod(int l, int r) {
    std::pair<ll, ll> v = {kMinVal, kMinVal};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) v = std::max(v, vals[l++]);
      if (r & 1) v = std::max(v, vals[--r]);
    }
    return v;
  }
};

class Solution {
  vector<ll> pre;

  pair<ll, int> work(int n, int l, int r, ll k) {
    std::vector<std::pair<ll, ll>> f(n + 1, {kMinVal, kMinVal});
    segtree seg(n + 1);
    seg.set(0, {0, 0});
    for (int i = 1; i <= n; i++) {
      int lb = i - r, rb = i - l + 1;  // [lb, rb) 之间的区间长度在 [l, r] 之间
      lb = std::max(lb, 0);
      rb = std::max(rb, 0);
      auto s = seg.prod(lb, rb);
      s.first += pre[i] - k;
      s.second++;
      s = std::max(s, f[i - 1]);
      f[i] = s;
      s = std::max(s, {0, 0});
      s.first -= pre[i];
      seg.set(i, s);
    }
    return f[n];
  };

 public:
  pair<ll, int> check(int n, int l, int r, ll cost) {
    vector<pair<ll, ll>> dp(n + 1, {0, 0});  // 选择任意个数的答案
    deque<int> q;
    dp[0] = {0, 0};

    for (int i = 1; i <= n; ++i) {
      dp[i] = dp[i - 1];

      int add = i - l;
      if (add >= 0) {
        ll val = dp[add].first - pre[add];
        while (!q.empty() && (dp[q.back()].first - pre[q.back()]) < val) {
          q.pop_back();
        }
        while (!q.empty() && (dp[q.back()].first - pre[q.back()]) == val && dp[q.back()].second > dp[add].second) {
          q.pop_back();
        }
        q.push_back(add);
      }

      while (!q.empty() && q.front() < i - r) {
        q.pop_front();
      }

      if (!q.empty()) {
        int best_k = q.front();
        ll current_sum = dp[best_k].first - pre[best_k] + pre[i] - cost;

        if (current_sum > dp[i].first || (current_sum == dp[i].first && dp[best_k].second + 1 < dp[i].second)) {
          dp[i] = {current_sum, dp[best_k].second + 1};
        }
      }
    }
    return dp[n];
  }
  ll Solver1(vector<int>& nums, int l, int r) {  //
    // 只能选择一个区间，长度在 [l, r] 之间
    // 单调队列维护区间最大区间和
    int n = nums.size();
    ll ans = kMinVal;
    deque<int> q;
    for (int i = 1; i <= n; ++i) {
      int left = i - l + 1;
      if (left > 0) {
        ll val = pre[i] - pre[left - 1];
        while (!q.empty() && (pre[i] - pre[q.back() - 1]) <= val) {
          q.pop_back();
        }
        q.push_back(left);
      }
      if (!q.empty()) {
        ans = max(ans, pre[i] - pre[q.front() - 1]);
      }
      while (!q.empty() && i - q.front() + 1 >= r) {
        q.pop_front();
      }
    }
    return ans;
  }

  ll maximumSum(vector<int>& nums, int m, int l, int r) {
    int n = nums.size();
    pre.resize(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      pre[i + 1] = pre[i] + nums[i];
    }
    m = min(m, n / l);
    if (m == 1) {
      ll ans = Solver1(nums, l, r);
      MyPrintf("m == 1,  ans = %lld\n", ans);
      return ans;
    }
    auto [max_sum, count] = check(n, l, r, 0);
    if (count > 0 && count <= m) {
      MyPrintf("count == %d < m, ans = %lld\n", count, max_sum);
      return max_sum;
    }
    if (count == 0) {
      ll ans = Solver1(nums, l, r);
      MyPrintf("count == 0,  ans = %lld\n", ans);
      return ans;
    }
    MyPrintf("count == %d > m, max_sum = %lld\n", count, max_sum);

    ll low = -2e13, high = 2e13;
    ll ans = 0;
    while (low <= high) {
      ll mid = (high + low) / 2;
      auto [sum, cnt] = check(n, l, r, mid);
      if (cnt >= m) {
        ans = sum + mid * m;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
    // ll mid = low + (high - low) / 2;
    // auto [max_sum1, count1] = work(n, l, r, mid);
    // MyPrintf("final mid = %lld, max_sum1 = %lld, count1 = %d\n", mid, max_sum1, count1);
    // return max_sum1 + count1 * mid;
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