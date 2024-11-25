/*
ID: tiankonguse
TASK: fc
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "fc"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK TASKEX);
#endif
}

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

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

vector<int> Graham(vector<Point>& p) {
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

  vector<int> ans;
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

void Solver() {  //
  int n;
  vector<Point> p;
  scanf("%d", &n);
  p.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lf%lf", &p[i].x, &p[i].y);
  }

  if (n <= 1) {
    printf("%.2f\n", 0.0);
  } else {
    vector<int> ret = Graham(p);
    double ans = dis(p[ret.front()], p[ret.back()]);
    for (int i = 0; i + 1 < int(ret.size()); i++) {
      ans += dis(p[ret[i]], p[ret[i + 1]]);
    }
    printf("%.2f\n", ans);
  }
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/