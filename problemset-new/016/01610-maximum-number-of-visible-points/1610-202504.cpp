
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
  int visiblePoints(vector<vector<int>>& points_, int angle, vector<int>& location) {
    // location = [posx, posy]
    // points[i] = [xi, yi]
    double toDegree = angle * M_PI / 180;
    vector<double> points;
    points.reserve(points_.size());
    int base = 0;
    for (auto& p : points_) {
      if (p[0] == location[0] && p[1] == location[1]) {
        base++;
        continue;  // 跳过与位置相同的点
      }
      points.push_back(atan2(p[1] - location[1], p[0] - location[0]));
      points.push_back(points.back() + 2 * M_PI);
    }

    sort(points.begin(), points.end());
    int n = points.size();
    int l = 0, r = 0;
    int ans = 0;
    auto updateAdd = [&](auto& v) {};
    auto updateDel = [&](auto& v) {};
    auto shouldMove = [&](double lv, double rv) -> bool { return rv - lv > toDegree; };
    while (r < n) {
      auto& rv = points[r];
      r++;
      updateAdd(rv);  // 第一步：移动右指针

      while (l < r && shouldMove(points[l], rv)) {
        auto& lv = points[l];
        l++;
        updateDel(lv);
      }

      ans = max(ans, r - l);  // 第三步：更新答案
    }
    return ans + base;
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