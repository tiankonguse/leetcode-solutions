
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
class Solution {
  vector<tuple<ll, ll, int>> emptys;
  ll minAns = 0;
  void Add(ll a, ll b, ll num) {
    if (a > b) {
      swap(a, b);
    }
    if (num == 0) {
      minAns = max(minAns, b - a);
    } else {
      // MyPrintf("add [%lld,%lld] num=%lld\n", a, b, num);
      emptys.push_back({a, b, num});
    }
  }
  bool Check(ll k) {  // 取两个值, x 取最小值+k， y 取最大值-k
    ll minVal = INT_MAX;
    ll maxVal = 1;
    for (auto [a, b, num] : emptys) {
      minVal = min(minVal, a);
      maxVal = max(maxVal, b);
    }
    ll x = minVal + k;
    ll y = maxVal - k;

    for (auto [a, b, num] : emptys) {
      if (abs(a - x) <= k && abs(b - x) <= k) continue;
      if (abs(a - y) <= k && abs(b - y) <= k) continue;
      if (num == 1) return false;
      if (abs(a - x) <= k && abs(b - y) <= k && abs(x - y) <= k) {
        continue;
      }
      return false;
    }

    return true;
  }

 public:
  int minDifference(vector<int>& nums) {
    ll pos = -1;  // 首个非 -1 的位置
    int n = nums.size();
    for (int i = 0; i < n; i++) {  //
      if (nums[i] == -1) continue;
      if (pos == -1) {  // (pos, i-1) 都是 -1
        if (i != 0) {
          Add(nums[i], nums[i], 1);
        }
      } else {
        Add(nums[pos], nums[i], i - pos - 1);
      }
      pos = i;
    }
    sort(emptys.begin(), emptys.end());

    ll l = minAns, r = INT_MAX;
    while (l < r) {
      ll mid = (l + r) / 2;
      if (Check(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return r;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  TEST_SMP1(Solution, minDifference, ans, jump);
}

int main() {
  Test({1, 2, -1, 10, 8}, 4);
  Test({-1, -1, -1}, 0);
  Test({-1, 10, -1, 8}, 1);
  Test({412, -1, -1, 42, 68, -1, 448, -1, 214}, 190);
  return 0;
}

#endif