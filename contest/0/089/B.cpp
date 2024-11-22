
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
  bool LessEq(pair<ll, ll> a, pair<ll, ll> b) {
    return a.first * b.second <= b.first * a.second;
  }

 public:
  int carFleet(const int target, const vector<int>& position,
               const vector<int>& speed) {
    const int n = position.size();

    vector<int> nums;
    nums.reserve(n);
    for (int i = 0; i < n; i++) {
      nums.push_back(i);
    }
    sort(nums.begin(), nums.end(), [&position, &speed](auto a, auto b) {
      if (position[a] == position[b]) {
        return speed[a] > speed[b];
      } else {
        return position[a] < position[b];
      }
    });
    std::reverse(nums.begin(), nums.end());

    int ans = 0;
    pair<ll, ll> useTime = {0, 1};
    for (const ll now : nums) {
      const ll P = position[now];
      const ll S = speed[now];
      MyPrintf("now=%lld p=%lld s=%lld\n", now, P, S);
      // 判断 时刻 t, now 是否可以追赶上 pre
      pair<ll, ll> nowTime = {target - P, S};
      MyPrintf("try[%lld] nowTime[%lld/%lld]\n", now, nowTime.first,
               nowTime.second);
      if (LessEq(nowTime, useTime)) {  // 可以追上
        MyPrintf("merge\n");
        continue;
      }
      ans++;
      useTime = nowTime;
      MyPrintf("new useTime[%lld/%lld]\n", useTime.first, useTime.second);
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(int target, const vector<int>& position, const vector<int>& speed,
          const int& ans) {
  TEST_SMP3(Solution, carFleet, ans, target, position, speed);
}

int main() {
  Test(12, {10, 8, 0, 5, 3}, {2, 4, 1, 1, 3}, 3);
  Test(10, {3}, {3}, 1);
  Test(100, {0, 2, 4}, {4, 2, 1}, 1);
  Test(17, {8, 12, 16, 11, 7}, {6, 9, 10, 9, 7}, 4);
  return 0;
}

#endif