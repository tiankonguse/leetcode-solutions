/*
ID: tiankonguse
TASK: fence4
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "fence4"
#define TASKEX "-ivorysi"

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

#define siji(i, x, y) for (int i = (x); i <= (y); ++i)
#define xiaosiji(i, x, y) for (int i = (x); i < (y); ++i)
#define ivorysi
#define eps 1e-8
#define o(x) ((x) * (x))
using namespace std;
typedef long long ll;
int n;
struct vec {
  double x, y;
  vec operator-(const vec &rhs) const { return (vec){x - rhs.x, y - rhs.y}; }
  vec operator+(const vec &rhs) const { return (vec){x + rhs.x, y + rhs.y}; }
  vec operator*(double d) const { return (vec){x * d, y * d}; }
  vec operator/(double d) const { return (vec){x / d, y / d}; }
  double norm() const { return x * x + y * y; }
} pt[205], observer;
struct line {
  vec s, t;
} seg[205];
bool visible[205];
int ans;
double cross(vec a, vec b) {  // 求叉积
  return a.x * b.y - b.x * a.y;
}
vec intersect(line a, line b) {  // 求交点
  double s1 = cross(b.s - a.s, b.t - a.s), s2 = cross(b.t - a.t, b.s - a.t);
  return a.s + (a.t - a.s) * s1 / (s1 + s2);
}
inline bool dcmp(double a, double b = 0) { return fabs(a - b) <= eps; }

bool iscross(line a, line b) {
  if (cross(a.t - a.s, b.s - a.s) * cross(a.t - a.s, b.t - a.s) >= 0 ||
      cross(b.t - b.s, a.s - b.s) * cross(b.t - b.s, a.t - b.s) >= 0)
    return false;
  return true;
}
void init() {
  scanf("%d", &n);
  scanf("%lf%lf", &observer.x, &observer.y);
  siji(i, 1, n) { scanf("%lf%lf", &pt[i].x, &pt[i].y); }
  siji(i, 1, n - 2) { seg[i].s = pt[i], seg[i].t = pt[i + 1]; }
  seg[n - 1].s = pt[1], seg[n - 1].t = pt[n];
  seg[n].s = pt[n - 1], seg[n].t = pt[n];
  siji(i, 1, n) {
    siji(j, 1, n) {
      if (i == j) continue;
      if (!iscross(seg[i], seg[j])) continue;
      puts("NOFENCE");
      exit(0);
    }
  }
}
void checkline(line l) {
  double shortest;
  int num = -1;
  siji(i, 1, n) {
    if (cross(seg[i].s - l.s, l.t - l.s) * cross(seg[i].t - l.s, l.t - l.s) >=
        0)
      continue;  // 射线只需要判定一个点
    vec temp = intersect(l, seg[i]) - l.s;
    if (temp.x * (l.t.x - l.s.x) < 0 || temp.y * (l.t.y - l.s.y) < 0)
      continue;  // 假如交点和射线上的点相乘小于0说明是不同方向
    if (num == -1) {
      num = i;
      shortest = temp.norm();
    } else if (shortest > temp.norm()) {
      shortest = temp.norm();
      num = i;
    }
  }
  if (num != -1) visible[num] = 1;
}
void Solver() {
  init();
  line l;
  l.s = observer;
  siji(i, 1, n) {
    double angle = atan2(pt[i].y - l.s.y, pt[i].x - l.s.x);
    l.t = l.s + (vec){cos(angle + eps), sin(angle + eps)};  // 偏上一点点
    checkline(l);
    l.t = l.s + (vec){cos(angle - eps), sin(angle - eps)};  // 偏下一点点
    checkline(l);
  }
  siji(i, 1, n) {
    if (visible[i]) ++ans;
  }
  printf("%d\n", ans);
  siji(i, 1, n) {
    if (visible[i])
      printf("%d %d %d %d\n", (int)seg[i].s.x, (int)seg[i].s.y, (int)seg[i].t.x,
             (int)seg[i].t.y);
  }
}
int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}
