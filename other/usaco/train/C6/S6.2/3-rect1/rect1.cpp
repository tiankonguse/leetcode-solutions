/*
ID: tiankonguse
TASK: rect1
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "rect1"
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

struct Point {
  int x, y;
  void Read() { scanf("%d%d", &x, &y); }
};

struct Node {
  Point a, b;
  int c;
  void Read() {
    a.Read();
    b.Read();
    scanf("%d", &c);
  }
};

int A, B, N, C;
vector<int> xh, yh;
unordered_map<int, int> XH, YH;
vector<Node> regions;
vector<int> g;
vector<int> ans;
void Solver() {  //
  scanf("%d%d%d", &A, &B, &N);
  xh.push_back(0);
  xh.push_back(A);
  yh.push_back(0);
  yh.push_back(B);
  regions.resize(N);
  C = 0;
  for (int i = 0; i < N; i++) {
    regions[i].Read();
    C = max(C, regions[i].c);
    xh.push_back(regions[i].a.x);
    xh.push_back(regions[i].b.x);

    yh.push_back(regions[i].a.y);
    yh.push_back(regions[i].b.y);
  }
  sort(xh.begin(), xh.end());
  xh.erase(unique(xh.begin(), xh.end()), xh.end());
  sort(yh.begin(), yh.end());
  yh.erase(unique(yh.begin(), yh.end()), yh.end());

  int XN = 0;
  for (auto v : xh) {
    XH[v] = XN;
    XN++;
  }

  int YN = 0;
  for (auto v : yh) {
    YH[v] = YN;
    YN++;
  }

  ans.resize(C + 1, 0);
  for (int i = 0; i < XH[A]; i++) {
    g.clear();
    g.resize(YN, 0);
    for (int j = 0; j < YH[B]; j++) {
      g[j] = 1;
    }
    for (auto& node : regions) {
      int X0 = XH[node.a.x];
      int Y0 = YH[node.a.y];
      int X1 = XH[node.b.x];
      int Y1 = YH[node.b.y];
      if (i >= X0 && i < X1) {
        for (int j = Y0; j < Y1; j++) {
          g[j] = node.c;
        }
      }
    }
    for (int j = 0; j < YH[B]; j++) {
      int c = g[j];
      int x0 = xh[i];
      int y0 = yh[j];
      int x1 = xh[i + 1];
      int y1 = yh[j + 1];
      ans[c] += (x1 - x0) * (y1 - y0);
    }
  }

  for (size_t i = 0; i < ans.size(); i++) {
    if (ans[i]) {
      printf("%d %d\n", int(i), ans[i]);
    }
  }
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*
Executing...
   Test 1: TEST OK [0.004 secs limit:1s, 1716 KB]
   Test 2: TEST OK [0.004 secs limit:1s, 1700 KB]
   Test 3: TEST OK [0.004 secs limit:1s, 1600 KB]
   Test 4: TEST OK [0.007 secs limit:1s, 1724 KB]
   Test 5: TEST OK [0.004 secs limit:1s, 1724 KB]
   Test 6: TEST OK [0.007 secs limit:1s, 1740 KB]
   Test 7: TEST OK [0.011 secs limit:1s, 1720 KB]
   Test 8: TEST OK [0.007 secs limit:1s, 1636 KB]
   Test 9: TEST OK [0.018 secs limit:1s, 1692 KB]
   Test 10: TEST OK [0.018 secs limit:1s, 1640 KB]
   Test 11: TEST OK [1.176 secs limit:2s, 3500 KB]

All tests OK.
*/