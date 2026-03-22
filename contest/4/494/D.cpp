
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
 public:
  long long countGoodSubarrays(vector<int>& nums) {
    int n = nums.size();

    unordered_map<int, vector<int>> pos;
    for (int i = 0; i < n; i++) {
      pos[nums[i]].push_back(i);
    }

    long long ans = 0;
    vector<pair<int, int>> cur;  // (or_value, 最左端点)
    for (int r = 0; r < n; r++) {
      int x = nums[r];

      vector<pair<int, int>> nxt;
      nxt.emplace_back(x, r);

      for (auto [v, l] : cur) {
        int nv = v | x;
        if (nxt.back().first == nv) {
          nxt.back().second = min(nxt.back().second, l);
        } else {
          nxt.emplace_back(nv, l);
        }
      }

      cur = nxt;
      int prev_l = r + 1;
      for (auto [v, l] : cur) {
        int L = l;
        int R = prev_l - 1;

        auto& vec = pos[v];
        auto it = upper_bound(vec.begin(), vec.end(), r);
        if (it != vec.begin()) {
          --it;
          int p = *it;

          int right = min(R, p);
          if (right >= L) {
            ans += (right - L + 1);
          }
        }
        prev_l = l;
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