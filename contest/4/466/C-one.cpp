
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
class Solution {
  inline int Abs(int x) { return x < 0 ? -x : x; }

 public:
  long long bowlSubarrays(vector<int>& nums) {
    int n = nums.size();
    vector<pair<int, int>> sta;  // (value, index) 单调递减
    sta.reserve(n);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
      const int v = nums[i];
      if (sta.size() > 1 && Abs(sta.back().first) < v) {  // 长度至少为 3
        auto it = std::lower_bound(sta.begin(), sta.end(), make_pair(-v, -1));
        ans += sta.end() - it - 1;
        if (it != sta.begin()) {
          ans++;  // 只能选择一个大于 右端点的值
        }
      }
      while (!sta.empty() && Abs(sta.back().first) <= v) {
        sta.pop_back();
      }
      sta.push_back({-v, i});
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