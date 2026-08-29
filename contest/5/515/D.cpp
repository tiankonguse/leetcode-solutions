
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 353 / 999 个通过的测试用例

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
typedef long long ll;
class Solution {
  vector<pair<ll, ll>> requests;  // arrivalTime, floor

 public:
  long long elevatorRequests(int n_, int start, vector<vector<int>>& requests_) {
    const int rn = requests_.size();
    requests.reserve(rn);
    for (auto& r : requests_) {
      requests.push_back({r[0], r[1]});
    }

    // dp[li][mask] 处于第 lev 个请求的楼层，访问了 mask 个请求的最小时间
    vector<vector<ll>> dp(rn + 1, vector<ll>(1 << rn, LLONG_MAX));
    min_queue<tuple<ll, int, int>> que;

    ll ans = LLONG_MAX;
    auto Add = [&](int ri, int mask, ll cost) {
      ll& ret = dp[ri][mask];
      if (cost < ret) {
        ret = cost;
        que.push({cost, ri, mask});
      }
      if (mask == (1 << rn) - 1) {
        ans = min(ans, cost);
      }
    };

    for (int i = 0; i < rn; i++) {
      auto [arrivalTime, floor] = requests[i];
      Add(i, 1 << i, max(arrivalTime, abs(floor - start)));
    }

    while (!que.empty()) {
      const auto [cost, ri, mask] = que.top();
      que.pop();
      if (dp[ri][mask] != cost) continue;  // 更优答案处理过了
      auto floorRi = requests[ri].second;
      for (int rj = 0; rj < rn; rj++) {
        if (mask & (1 << rj)) continue;
        auto [arrivalTimeRj, floorRj] = requests[rj];
        ll newCost = 0;
        if (arrivalTimeRj >= cost) {
          newCost = cost + max(abs(arrivalTimeRj - cost), abs(floorRj - floorRi));
        } else {
          newCost = cost + abs(floorRj - floorRi);
        }
        Add(rj, mask | (1 << rj), newCost);
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