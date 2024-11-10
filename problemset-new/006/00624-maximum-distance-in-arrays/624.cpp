
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
  int maxDistance(const vector<vector<int>>& arrays) {
    vector<pair<int, int>> minVal;
    vector<pair<int, int>> maxVal;

    auto AddMin = [&arrays, &minVal](int i, int j) {
      minVal.push_back({i, j});
      for (int i = minVal.size() - 1; i > 0; i--) {
        auto [x0, y0] = minVal[i - 1];
        auto [x1, y1] = minVal[i];
        if (arrays[x0][y0] > arrays[x1][y1]) {
          swap(minVal[i - 1], minVal[i]);
        }
      }
      if (minVal.size() > 2) {
        minVal.pop_back();
      }
    };
    auto AddMax = [&arrays, &maxVal](int i, int j) {
      maxVal.push_back({i, j});
      for (int i = maxVal.size() - 1; i > 0; i--) {
        auto [x0, y0] = maxVal[i - 1];
        auto [x1, y1] = maxVal[i];
        if (arrays[x0][y0] < arrays[x1][y1]) {
          swap(maxVal[i - 1], maxVal[i]);
        }
      }
      if (maxVal.size() > 2) {
        maxVal.pop_back();
      }
    };

    for (size_t i = 0; i < arrays.size(); i++) {
      AddMin(i, 0);
      AddMax(i, arrays[i].size() - 1);
    }

    int ans = 0;
    for (auto [x0, y0] : minVal) {
      for (auto [x1, y1] : maxVal) {
        if (x0 == x1) continue;  // 同一个数组
        ans = max(ans, abs(arrays[x0][y0] - arrays[x1][y1]));
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<vector<int>>& arrays, const int& ans) {
  TEST_SMP1(Solution, maxDistance, ans, arrays);
}

int main() {
  Test({{1, 2, 3}, {4, 5}, {1, 2, 3}}, 4);
  Test({{1}, {1}}, 0);
  Test({{-3, -3, -1, -1}, {-3, -2}}, 2);
  Test({{1}, {2}}, 1);
  return 0;
}

#endif