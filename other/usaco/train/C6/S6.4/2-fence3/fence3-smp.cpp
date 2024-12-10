/*
ID: tiankonguse
TASK: fence3
LANG: C++
MAC EOF: ctrl+D
DESC: 直接枚举 0.1 粒度的所有点，第9组超时
*/
#define TASK "fence3"
#define TASKEX "-smp"

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

int n;
struct Point {
  int x, y;
  void Read() { scanf("%d%d", &x, &y); }
  pair<int, int> P() { return {x, y}; }
};

struct Line {
  Point a, b;
  void Read() {
    a.Read();
    b.Read();
    if (a.x > b.x || a.y > b.y) {
      swap(a, b);  // 从左到右，从下到上
    }
  }
  pair<int, int> First() { return a.P(); }
  pair<int, int> Second() { return b.P(); }
};
vector<Line> lines;
double Dis(double x0, double y0, double x1, double y1) {
  return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}

double Cal(double X, double Y) {
  double ret = 0;
  for (auto& line : lines) {
    auto [x0, y0] = line.First();
    auto [x1, y1] = line.Second();
    if (y0 == y1) {  // 横线
      if (X <= x0) {
        ret += Dis(X, Y, x0, y0);
      } else if (X >= x1) {
        ret += Dis(X, Y, x1, y1);
      } else {
        ret += fabs(Y - y0);
      }
    } else {  // 竖线 x0==x1
      if (Y <= y0) {
        ret += Dis(X, Y, x0, y0);
      } else if (Y >= y1) {
        ret += Dis(X, Y, x1, y1);
      } else {
        ret += fabs(X - x0);
      }
    }
  }
  return ret;
}


double ansX = 0, ansY = 0, ansD = INT_MAX;

void Update(const int x, const int y) {
  const double X = x / 10.0;
  const double Y = y / 10.0;
  const double D = Cal(X, Y);
  // if (x == 159 && y == 159) {
  //   printf("x=%d y=%d D=%.6f\n", x, y, D);
  // }
  if (D < ansD) {
    ansD = D;
    ansX = X;
    ansY = Y;
  }
}


int UP = 0, DOWN = 1000, LEFT = 1000, RIGHT = 0;
void Solver() {  //
  scanf("%d", &n);
  lines.resize(n);
  for (int i = 0; i < n; i++) {
    lines[i].Read();
    LEFT = min(LEFT, min(lines[i].a.x, lines[i].b.x));
    RIGHT = max(RIGHT, max(lines[i].a.x, lines[i].b.x));

    DOWN = min(DOWN, min(lines[i].a.y, lines[i].b.y));
    UP = max(UP, max(lines[i].a.y, lines[i].b.y));
  }
  // printf("left=%d right=%d down=%d up=%d\n", LEFT, RIGHT, DOWN, UP);

  for (int x = LEFT * 10; x <= RIGHT * 10; x++) {
    for (int y = DOWN * 10; y <= UP * 10; y++) {
      Update(x, y);
    }
  }

  printf("%.1f %.1f %.1f\n", ansX, ansY, ansD);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*
Executing...
   Test 1: TEST OK [0.004 secs limit:1s, 1768 KB]
   Test 2: TEST OK [0.004 secs limit:1s, 1704 KB]
   Test 3: TEST OK [0.007 secs limit:1s, 1664 KB]
   Test 4: TEST OK [0.011 secs limit:1s, 1708 KB]
   Test 5: TEST OK [0.108 secs limit:1s, 1680 KB]
   Test 6: TEST OK [0.056 secs limit:1s, 1684 KB]
   Test 7: TEST OK [0.854 secs limit:1s, 1672 KB]
   Test 8: TEST OK [0.843 secs limit:1s, 1740 KB]
  > Run 9: Execution error: Your program (`fence3') used more than the
        allotted runtime of 1 seconds (it ended or was stopped at 1.148
        seconds) when presented with test case 9. It used 1728 KB of
        memory. 

        ------ Data for Run 9 [length=1174 bytes] ------
        100 
        ... [and more] ...
        ----------------------------
    Test 9: RUNTIME 1.148>1 (1728 KB)
*/