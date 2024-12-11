/*
ID: tiankonguse
TASK: fence4
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "fence4"
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

typedef double ftype;
struct point2d {
  ftype x, y;
  point2d() {}
  point2d(ftype x, ftype y) : x(x), y(y) {}
  point2d& operator+=(const point2d& t) {
    x += t.x;
    y += t.y;
    return *this;
  }
  point2d& operator-=(const point2d& t) {
    x -= t.x;
    y -= t.y;
    return *this;
  }
  point2d& operator*=(ftype t) {
    x *= t;
    y *= t;
    return *this;
  }
  point2d& operator/=(ftype t) {
    x /= t;
    y /= t;
    return *this;
  }
  point2d operator+(const point2d& t) const { return point2d(*this) += t; }
  point2d operator-(const point2d& t) const { return point2d(*this) -= t; }
  point2d operator*(ftype t) const { return point2d(*this) *= t; }
  point2d operator/(ftype t) const { return point2d(*this) /= t; }
  long long cross(const point2d& p) const { return x * p.y - y * p.x; }
  long long cross(const point2d& a, const point2d& b) const {
    return (a - *this).cross(b - *this);
  }
  void Read() { scanf("%lf%lf", &x, &y); }
};
point2d operator*(ftype a, point2d b) { return b * a; }

int sgn(const long long& x) { return x >= 0 ? x ? 1 : 0 : -1; }

bool inter1(long long a, long long b, long long c, long long d) {
  if (a > b) swap(a, b);
  if (c > d) swap(c, d);
  return max(a, c) <= min(b, d);
}

bool check_inter(const point2d& a, const point2d& b, const point2d& c,
                 const point2d& d) {
  if (c.cross(a, d) == 0 && c.cross(b, d) == 0)
    return inter1(a.x, b.x, c.x, d.x) && inter1(a.y, b.y, c.y, d.y);
  return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) &&
         sgn(c.cross(d, a)) != sgn(c.cross(d, b));
}

ftype dot(point2d a, point2d b) { return a.x * b.x + a.y * b.y; }
ftype norm(point2d a) { return dot(a, a); }
double abs(point2d a) { return sqrt(norm(a)); }
double proj(point2d a, point2d b) { return dot(a, b) / abs(b); }
double angle(point2d a, point2d b) {
  return acos(dot(a, b) * 1.0 / abs(a) / abs(b));
}
double angle(point2d a) { return atan2(a.y, a.x); }

double cross(point2d a, point2d b) {  // 求叉积
  return a.x * b.y - b.x * a.y;
}

// 直线 (a,b) 是否与线段 [c,d] 相交
// 不相交时，c 和 d 在直线的同一侧，向量叉乘符号相同
bool isCross(const point2d& sa, const point2d& sb, const point2d& ta,
             const point2d& tb) {
  return cross(ta - sa, sb - sa) * cross(tb - sa, sb - sa) >= 0;
}

int n;
vector<point2d> pts;
point2d p;
const point2d one(1, 0);

bool Valid() {
  for (int i = 0; i + 1 < n; i++) {         // [i,i+1]
    for (int j = i + 2; j + 1 <= n; j++) {  // [j, j+1]
      if (check_inter(pts[i], pts[i + 1], pts[j], pts[j + 1])) {
        return false;
      }
    }
  }
  return true;
}

vector<int> ans;

void CheckLine(point2d s, point2d t) {
  for (int i = 0; i < n; i++) {
    if (isCross(s, t, pts[i], pts[i + 1])) continue;
    
  }
}

void Solver() {  //
  scanf("%d", &n);
  p.Read();
  pts.resize(n + 1);
  for (int i = 0; i < n; i++) {
    pts[i].Read();
  }
  pts[n] = pts[0];
  if (!Valid()) {
    printf("NOFENCE\n");
    return;
  }

  ans.resize(n + 1, 0);
  for (int i = 0; i < n; i++) {
    double ang = angle(pts[i] - p);
    point2d t = p + point2d(cos(ang + eps), sin(ang + eps));
    CheckLine(p, t);
    t = p + point2d(cos(ang - eps), sin(ang - eps));
    CheckLine(p, t);
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