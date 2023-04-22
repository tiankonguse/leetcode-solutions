// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<int>> forceField;
  void Init() {
    // 扩大 2 倍，解决小数问题
    for (auto& vs : forceField) {
      for (auto& v : vs) {
        v = v * 2;
      }
    }
  }

  map<ll, int> hx, hy;
  int hxn = 0;
  int hyn = 0;
  vector<tuple<int, int, int, int>> nums;
  void LiSanHua() {
    hx.clear();
    hy.clear();
    for (auto& vs : forceField) {
      ll cx = vs[0], cy = vs[1], cr = vs[2]/2;
      ll x0 = cx - cr, x1 = cx + cr;
      ll y0 = cy - cr, y1 = cy + cr;
      // printf("[%d,%d,%d]->(%lld,%lld)(%lld,%lld),", cx, cy, cr, x0, x1, y0, y1);

      hx[x0] = -1;
      hx[x1] = -1;

      hy[y0] = -1;
      hy[y1] = -1;
    }
    // printf("\n");

    hxn = 0;
    for (auto& [x, v] : hx) {
      v = hxn++;
      // printf("%lld->%d,", x, v);
    }
    // printf("\n");

    hyn = 0;
    for (auto& [y, v] : hy) {
      v = hyn++;
      // printf("%lld->%d,", y, v);
    }
    // printf("\n");

    nums.clear();
    nums.reserve(forceField.size() * 2);
    for (auto& vs : forceField) {
      ll cx = vs[0], cy = vs[1], cr = vs[2]/2;
      ll x0 = cx - cr, x1 = cx + cr;
      ll y0 = cy - cr, y1 = cy + cr;

      int xx0 = hx[x0], xx1 = hx[x1];
      int yy0 = hy[y0], yy1 = hy[y1];
      nums.push_back({xx0, 1, yy0, yy1});
      nums.push_back({xx1, -1, yy0, yy1});
    }
  }

 public:
  int fieldOfGreatestBlessing(vector<vector<int>>& forceField_) {
    forceField.swap(forceField_);

    Init();
    LiSanHua();

    sort(nums.begin(), nums.end(), [](auto& a, auto& b) {
      auto [ax, aop, ay0, ay1] = a;
      auto [bx, bop, by0, by1] = b;

      if (ax != bx) {
        return ax < bx;  // 小的在前面
      } else {
        return aop > bop;  // 1 在前面, -1 在后面
      }
    });

    int ans = 0;
    // printf("\n");
    vector<int> lines(hyn + 1, 0);
    for (auto [x, op, y0, y1] : nums) {
      // printf("x=%d op=%d y0=%d y1=%d\n", x, op, y0, y1);
      for (int y = y0; y <= y1; y++) {
        lines[y] += op;
        ans = max(ans, lines[y]);
      }
      // for (int y = 0; y < hyn; y++) {
      //   printf("%d ", lines[y]);
      // }
      // printf("\n");
    }

    return ans;
  }
};