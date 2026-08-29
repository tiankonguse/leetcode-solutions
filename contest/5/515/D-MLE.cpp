
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
  int n;                          // [1,n]
  vector<pair<ll, ll>> requests;  // arrivalTime, floor

  vector<pair<int, int>> masksMinMax;  // {minOffset, maxOffset}
  vector<vector<int>> rangeMask;

  ll Process(int li, int mask) {  // 可以预处理
    if (mask == 0) return 0;
    auto [minOffset, maxOffset] = masksMinMax[mask];
    if (li <= minOffset) {
      return maxOffset - li;
    } else if (li >= maxOffset) {
      return li - minOffset;
    } else {
      return (maxOffset - minOffset) + min(li - minOffset, maxOffset - li);
    }
  }
  void Init() {
    masksMinMax.resize(1 << n, make_pair(0, 0));
    for (int mask = 1; mask < (1 << n); mask++) {
      int minOffset = n, maxOffset = -1;
      for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
          minOffset = min(minOffset, i);
          maxOffset = max(maxOffset, i);
        }
      }
      masksMinMax[mask] = make_pair(minOffset, maxOffset);
    }

    rangeMask.resize(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        if (j == i) {  // [i, i]
          rangeMask[i][j] = 1 << j;
        } else {
          rangeMask[i][j] = rangeMask[i][j - 1] | (1 << j);
        }
      }
    }
  }

 public:
  long long elevatorRequests(int n_, int start, vector<vector<int>>& requests_) {
    n = n_;
    Init();
    const int rn = requests_.size();
    requests.reserve(rn);
    for (auto& r : requests_) {
      requests.push_back({r[0], r[1]});
    }
    sort(requests.begin(), requests.end());

    // dp[ri][li][mask] 第 ri 个请求对应的时间，处于第 li 层，还有 mask 个楼层待处理时的最小代价
    vector<vector<vector<ll>>> dp(rn + 1, vector<vector<ll>>(n + 1, vector<ll>(1 << n, -1)));
    min_queue<tuple<ll, int, int, int>> que;

    auto Add = [&](int ri, int li, int mask, ll cost) {
      ll& ret = dp[ri][li][mask];
      if (ret == -1) {
        ret = cost;
        que.push({cost, ri, li, mask});
      }
    };
    Add(0, start, 0, 0);

    ll ans = LLONG_MAX;
    while (!que.empty()) {
      auto [cost, ri, li, mask] = que.top();
      que.pop();
      // if (dp[ri][li][mask] != cost) continue;  // 更优答案处理过了
      ll nowTime = 0;
      if (ri != 0) {
        nowTime = requests[ri - 1].first;
      }
      MyPrintf("pop: ri=%d, li=%d, mask=%d, cost=%lld nowTime=%lld\n", ri, li, mask, cost, nowTime);
      if (ri == rn) {  // 没有新的请求了，只需要把 mask 处理完就可以了
        ll tmpAns = nowTime + Process(li, mask);
        MyPrintf("end: tmpAns=%lld\n", tmpAns);
        ans = min(ans, tmpAns);
        continue;
      }
      auto [nextArrivalTime, nextFloor] = requests[ri];
      ll disTime = nextArrivalTime - nowTime;
      MyPrintf("nextArrivalTime=%lld, nextFloor=%lld, disTime=%lld\n", nextArrivalTime, nextFloor, disTime);
      // 下个请求的时间，处于 lj 楼层，还有 mask 个楼层待处理时的最小代价
      for (int lj = 0; lj < n; lj++) {
        if (disTime < abs(li - lj)) continue;  // 不可到达
        MyPrintf("li=%d -> lj=%d\n", li, lj);
        int extMask = (1 << nextFloor);
        if (lj == nextFloor) {
          extMask = 0;
        }
        int tmpLi = li;
        int tmpLj = lj;
        if (tmpLi > tmpLj) {  // 保证 tmpLi <= tmpLj
          swap(tmpLi, tmpLj);
        }
        if (mask == 0) {
          MyPrintf("mask=0, Add ri=%d lj=%d mask=%d, time=%lld\n", ri + 1, lj, extMask, nextArrivalTime);
          Add(ri + 1, lj, extMask, nextArrivalTime);
          continue;
        }

        auto [minOffset, maxOffset] = masksMinMax[mask];
        minOffset = min(minOffset, tmpLi);
        maxOffset = max(maxOffset, tmpLj);

        MyPrintf("minOffset=%d, maxOffset=%d, tmpLi=%d tmpLj=%d\n", minOffset, maxOffset, tmpLi, tmpLj);

        // 时间足够大，可以走遍所有 mask 的楼层
        if (disTime >= 2 * (maxOffset - minOffset) - (tmpLj - tmpLi)) {
          MyPrintf("时间足够大, Add ri=%d lj=%d mask=%d, time=%lld\n", ri + 1, lj, extMask, nextArrivalTime);
          Add(ri + 1, lj, extMask, nextArrivalTime);
          continue;
        }

        for (int offseti = minOffset; offseti <= tmpLi; offseti++) {
          for (int offsetj = tmpLj; offsetj <= maxOffset; offsetj++) {
            if (disTime >= 2 * (offsetj - offseti) - (tmpLj - tmpLi)) {
              // [offseti, offsetj] 中的 mask 都可以消除
              int eliminatedMask = rangeMask[offseti][offsetj];
              MyPrintf("枚举 offseti=%d offsetj=%d , Add ri=%d lj=%d mask=%d, time=%lld\n", offseti, offsetj, ri + 1,
                       lj, (mask & ~eliminatedMask) | extMask, nextArrivalTime);
              Add(ri + 1, lj, (mask & ~eliminatedMask) | extMask, nextArrivalTime);
            }
          }
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