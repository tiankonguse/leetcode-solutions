
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  ll maximumCoins(vector<vector<int>>& coins, int k) {
    sort(coins.begin(), coins.end());
    ll ans = 0;
    deque<tuple<ll, ll, ll>> que;  // {L, R, V} 区间 [L,R] 每个价值是 V
    ll sum = 0;                    // 当前区间和
    auto Update = [&ans](ll v) {   //
      ans = max(ans, v);
    };
    for (auto& coin : coins) {
      const ll l = coin[0], r = coin[1], v = coin[2];
      MyPrintf("coin: l=%lld r=%lld v=%lld\n", l, r, v);

      auto AddBack = [&que, &sum, &Update](ll l, ll r, ll v) {
        sum += v * (r - l + 1);
        Update(sum);

        if (que.empty()) {
          que.push_back({l, r, v});
          return;
        }

        auto [L, R, V] = que.back();
        if (R + 1 == l && V == v) {  // 连续
          que.pop_back();
          que.push_back({L, r, v});
        } else {
          que.push_back({l, r, v});
        }
      };

      // 开始等价交换
      ll li = l;
      while (li <= r && !que.empty() && r - get<0>(que.front()) + 1 > k) {
        if (li - get<0>(que.front()) < k) {
          int ri = min(get<0>(que.front()) + k - 1, r);  // 先左对齐
          AddBack(li, ri, v);
          li = ri + 1;
          continue;
        }

        auto [L, R, V] = que.front();

        que.pop_front();
        sum -= V * (R - L + 1);
        if (!que.empty() && l - (R + 1) + 1 >= k) {
          continue;  // 前一个区间都删除，剩余的依旧满足 k 个
        }
        MyPrintf("check: L=%lld R=%lld V=%lld li=%lld\n", L, R, V, li);

        if (R + 1 == li && V == v) {  // 只剩余一个区间
          sum = 0;
          if (r - L + 1 <= k) {
            AddBack(L, r, v);
          } else {
            AddBack(r - k + 1, r, v);
          }
          li = r + 1;
          break;
        }

        // 先补足 k 个

        if (r - (R + 1) + 1 >= k) {  // [R+1,r]>= k 可以把左区间全部删除
          ll ri = (R + 1) + k - 1;
          if (!que.empty()) {  // 跳过空白
            ll tmpL = get<0>(que.front());
            ri = min(r, tmpL + k - 1);
          }
          AddBack(li, ri, v);
          MyPrintf("check: pop all, add li=%lld ri=%lld sum=%lld ans=%lld\n", li, ri, sum, ans);
          li = ri + 1;
        } else {  // 左区间保留部分
          ll ri = r;
          ll X = ri - k + 1;  // 保留[X, R]
          sum += V * (R - X + 1);
          que.push_front({X, R, V});
          MyPrintf("check: pop part, add front X=%lld R=%lld sum=%lld\n", X, R, sum);

          AddBack(li, ri, v);
          MyPrintf("check: pop part, add back li=%lld ri=%lld sum=%lld ans=%lld\n", li, ri, sum, ans);
          li = ri + 1;
        }
      }

      if (que.empty()) {  // 说明当前区间 [l,r] >=k 或者区间之间相隔太远，前面的都删除了
        if (r - l + 1 <= k) {
          AddBack(l, r, v);
          MyPrintf("add full coin, l=%lld r=%lld v=%lld sum=%lld ans=%lld\n", l, r, v, sum, ans);
        } else {
          MyPrintf("add part coin, l=%lld r=%lld v=%lld sum=%lld ans=%lld\n", r - k + 1, r, v, sum, ans);
          AddBack(r - k + 1, r, v);
        }
      } else {
        if (li <= r) {
          AddBack(li, r, v);
          MyPrintf("add left coin, l=%lld r=%lld v=%lld sum=%lld ans=%lld\n", li, r, v, sum, ans);
        }
      }
    }

    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<vector<int>> coins, int k, ll ans) {  //
  TEST_SMP2(Solution, maximumCoins, ans, coins, k);
}

int main() {
  Test({{35, 37, 15},
        {3, 9, 1},
        {31, 33, 20},
        {10, 15, 6},
        {1, 2, 5},
        {38, 39, 8},
        {20, 23, 16},
        {48, 49, 3},
        {40, 43, 4},
        {29, 30, 16}},
       42, 282);
  return 0;
}

#endif