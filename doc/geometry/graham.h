// graham 算法，求凸包
// 思想：

#include <vector>

struct Point {
  int x, y;
};

bool mult(const Point &sp, const Point &ep, const Point &op) {
  return (sp.x - op.x) * (ep.y - op.y) > (ep.x - op.x) * (sp.y - op.y);
}
bool operator<(const Point &l, const Point &r) {
  return l.y < r.y || (l.y == r.y && l.x < r.x);
}
vector<Point> graham(std::vector<Point> &pnt) {
  int n = pnt.size();
  sort(pnt.begin(), pnt.end());
  std::vector<Point> res;
  res.push_back(pnt[0]);

  for (int i = 1; i < n; i++) {
    while (res.size() > 1 && mult(pnt[i], res.back(), res[res.size() - 2])) {
      res.pop_back();
    }
    res.push_back(pnt[i]);
  }

  int m = res.size();
  for (int i = n - 2; i >= 0; i--) {
    while (res.size() > m && mult(pnt[i], res.back(), res[res.size() - 2])) {
      res.pop_back();
    }
    res.push_back(pnt[i]);
  }
  if (res.size() > 1) {
    res.pop_back();
  }

  sort(res.begin(), res.end());

  std::vector<Point> ans;
  for (auto &p : res) {
    if (ans.empty() || (ans.back().x != p.x || ans.back().y != p.y)) {
      ans.push_back(p);
    }
  }
  return ans;
}