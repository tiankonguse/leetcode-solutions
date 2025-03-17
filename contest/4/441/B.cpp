
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
 public:
  vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
    int n = nums.size();
    unordered_map<int, vector<int>> group;
    for (int i = 0; i < n; i++) {
      group[nums[i]].push_back(i);
    }

    auto Dis = [n](int a, int b) {  //
      if (a < b) swap(a, b);
      return min(abs(a - b), abs(b + n - a));
    };

    int m = queries.size();
    vector<int> ans(m, -1);
    for (int i = 0; i < m; i++) {
      int j = queries[i];
      int v = nums[j];
      const auto& vec = group[v];
      int len = vec.size();
      printf("i=%d j=%d v=%d len=%d\n", i, j, v, len);
      if (len == 1) {
        continue;
      }

      auto it = lower_bound(vec.begin(), vec.end(), j);
      ans[i] = INT_MAX;

      auto nextIt = it;
      nextIt++;
      if (nextIt != vec.end()) {  // 下一个
        ans[i] = min(ans[i], Dis(j, *nextIt));
      } else {
        ans[i] = min(ans[i], Dis(j, vec.front()));
      }

      if (it != vec.begin()) {  // 上一个
        auto preIt = it;
        preIt--;
        ans[i] = min(ans[i], Dis(j, *preIt));
      } else {
        ans[i] = min(ans[i], Dis(j, vec.back()));
      }
    }

    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

int main() {  //
  return 0;
}

#endif