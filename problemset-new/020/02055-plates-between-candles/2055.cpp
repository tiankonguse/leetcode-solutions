
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

typedef long long ll;
class Solution {
 public:
  int maximizeWin(vector<int>& prizePositions, int k) {
    int n = prizePositions.size();
    ll ans = 0;
    int l = 0, r = 0;
    map<ll, ll> leftMax;
    map<ll, ll> rightSum;
    ll sum = 0, maxSum = 0;
    leftMax[0] = 0;
    auto updateAdd = [&](auto& v) { sum += 1; };
    auto updateDel = [&](auto& v) { sum -= 1; };
    auto shouldMove = [&](auto& lv, auto& rv) -> bool { return rv - lv > k; };
    while (r < n) {
      auto& rv = prizePositions[r];
      r++;
      updateAdd(rv);  // 第一步：移动右指针

      while (shouldMove(prizePositions[l], rv)) {  // 第二步：移动左指针
        auto& lv = prizePositions[l];
        l++;
        updateDel(lv);
      }
      auto& lv = prizePositions[l];
      rightSum[lv] = max(rightSum[lv], sum);

      auto it = leftMax.lower_bound(lv);
      it--;
      ans = max(ans, sum + it->second);

      maxSum = max(maxSum, sum);
      leftMax[rv] = maxSum;
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