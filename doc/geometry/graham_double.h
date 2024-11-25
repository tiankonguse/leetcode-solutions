// graham 算法，求凸包
// 思想：

#include <vector>

struct Point {
  double x, y, ang;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y, 0}; }
};

double cross(Point p1, Point p2) { return p1.x * p2.y - p1.y * p2.x; }
double dis(Point p1, Point p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

std::vector<int> Graham(std::vector<Point>& p) {
  int n = p.size();
  const int S = 0;

  for (int i = 1; i < n; ++i) {
    if (p[i].y < p[S].y || (p[i].y == p[S].y && p[i].x < p[S].x)) {
      std::swap(p[S], p[i]);
    }
  }

  for (int i = S; i < n; ++i) {
    p[i].ang = atan2(p[i].y - p[S].y, p[i].x - p[S].x);
  }
  std::sort(++p.begin(), p.end(),
            [&p0 = p[S]](const Point& p1, const Point& p2) {
              if (p1.ang == p2.ang) {
                return dis(p1, p0) < dis(p2, p0);
              }
              return p1.ang < p2.ang;
            });

  std::vector<int> ans;
  ans.push_back(S);
  for (int i = 1; i < n; ++i) {
    while (int(ans.size()) >= 2 &&
           cross(p[ans[ans.size() - 1]] - p[ans[ans.size() - 2]],
                 p[i] - p[ans[ans.size() - 1]]) < 0) {
      ans.pop_back();
    }
    ans.push_back(i);
  }
  return ans;
}