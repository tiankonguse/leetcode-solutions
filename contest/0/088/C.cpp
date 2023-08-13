// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
typedef long long ll;
class Solution {
  struct Rect {
    ll left = 0;
    ll bottom = 0;
    ll right = 0;
    ll top = 0;
  };

 public:
  // n=200
  int rectangleArea(vector<vector<int>>& rectangles) {
    set<ll> hy;
    vector<Rect> rects;
    for (auto& v : rectangles) {
      // (xi1, yi1) 是左下角坐标， (xi2, yi2) 是右上角 的坐标。
      Rect rect{v[0], v[1], v[2], v[03]};
      rects.push_back(rect);
      hy.insert(rect.top);
      hy.insert(rect.bottom);
    }

    vector<tuple<ll, ll, ll>> ranges;
    ll pre = -1;
    for (auto& k : hy) {
      ranges.push_back({pre, k, 0});
      pre = k;
    }

    sort(rects.begin(), rects.end(), [](auto& a, auto& b) {
      if (a.left != b.left) {
        return a.left < b.left;
      }
      return a.bottom < b.bottom;
    });

    ll ans = 0;
    vector<ll> hights(ranges.size(), 0);
    for (auto& rect : rects) {
      for (auto& [bottom, top, h] : ranges) {
        if (top <= rect.bottom || rect.top <= bottom) continue;
        h = max(h, rect.left);
        if (h < rect.right) {
          ans += (rect.right - h) * (top - bottom);
          h = rect.right;
        }
      }
    }

    return ans % mod;
  }
};
