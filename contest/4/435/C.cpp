
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
// GCD 相关算法

// 推论1：有俩个数p,q,且gcd(q,p)=1,则最大无法表示成px+qy（x>=0,y>=0)的数是pq-q-p.

// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t);
  return y;
}
ll Lcm(ll x, ll y) {
  if (x == 0) x = 1;
  if (y == 0) y = 1;
  return x / Gcd(x, y) * y;
}
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;

class Solution {
  vector<ll> buf;
  vector<int> target;
  vector<int> nums;
  vector<int> nums0;
  vector<vector<ll>> dp;
  ll ans = LLONG_MAX;
  vector<int> use;
  min_queue<tuple<ll, ll, ll>> que;

  void InitNums() {
    int m = buf.size();
    int n = nums.size();

    use.resize(n);
    for (int i = 0; i < n; i++) {
      use[i] = 0;
    }

    for (int i = 0; i < m; i++) {
      int V = buf[i];

      for (int j = 0; j < n; j++) {
        int v = nums[j];
        ll left = v % V;
        if (left == 0) left = V;
        que.push({left, v, j});
        if (que.size() > m) {
          que.pop();
        }
      }

      while (!que.empty()) {
        auto [left, v, j] = que.top();
        use[j] = 1;
        que.pop();
      }
    }

    nums0.clear();
    for (int i = 0; i < n; i++) {
      if (use[i]) {
        nums0.push_back(nums[i]);
      }
    }
  }
  void Solver() {
    InitNums();
    int m = buf.size();
    int n = nums0.size();
    // printf("buf: ");
    // for (auto v : buf) {
    //   printf("%lld ", v);
    // }
    // printf("\n");
    // printf("nums0: ");
    // for (auto v : nums0) {
    //   printf("%lld ", v);
    // }
    // printf("\n");
    // printf("m=%d n=%d\n", m, n);

    // dp[i][j] = min(dp[i-1][j], Cost(i,j) + dp[i-1][j-1])
    for (int i = 0; i <= n; i++) {
      dp[i][0] = 0;
      for (int j = 1; j <= m; j++) {
        dp[i][j] = LLONG_MAX / 2;
      }
    }

    for (int i = 1; i <= n; i++) {
      const int v = nums0[i - 1];
      for (int j = 1; j <= m && j <= i; j++) {
        const ll V = buf[j - 1];
        const ll add = (V - v % V) % V;
        dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1] + add);
      }
    }

    ans = min(ans, dp[n][m]);
    // printf("ans=%lld\n", dp[n][m]);
  }
  void Dfs(const ll pre, const int pos = 0) {
    const int m = target.size();
    if (m == 0) {
      if (pre) buf.push_back(pre);
      Solver();
      if (pre) buf.pop_back();
      return;
    }

    if (pre == 0) {                  // 必须选择一个，贪心选择最后一个
      for (int i = 0; i < m; i++) {  // 选择 i
        const ll selectVal = target[i];
        swap(target[i], target.back());
        target.pop_back();

        Dfs(selectVal, 0);  // 选择一个后，后面的必须有序选择

        target.push_back(selectVal);
        swap(target[i], target.back());
      }
    } else {
      for (int i = pos; i < m; i++) {  // 选择 i
        const ll selectVal = target[i];

        swap(target[i], target.back());
        target.pop_back();

        Dfs(Lcm(pre, selectVal), i);  // 第 i 个和最后个置换，下次继续从第 i 个开始选择

        target.push_back(selectVal);
        swap(target[i], target.back());
      }

      // 选择结束
      if (pre) {
        buf.push_back(pre);
        Dfs(0);
        buf.pop_back();
      }
    }
  }

 public:
  int minimumIncrements(vector<int>& nums_, vector<int>& target_) {
    target.swap(target_);
    unordered_map<int, int> h;
    for (auto v : nums_) {
      h[v]++;
    }
    nums.reserve(nums_.size());
    for (auto [k, v] : h) {
      for (int i = 0; i < 4 && i < v; i++) {
        nums.push_back(k);
      }
    }
    dp.resize(16 + 1, vector<ll>(target.size() + 1, LLONG_MAX / 2));
    Dfs(0);
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