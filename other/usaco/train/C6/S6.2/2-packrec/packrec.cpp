/*
ID: tiankonguse
TASK: packrec
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "packrec"
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

int N = 4;
int ans;
vector<pair<int, int>> ansPoints;

vector<pair<int, int>> points;

void Update(int x, int y) {
  if (x > y) {
    swap(x, y);
  }
  int tmp = x * y;
  if (tmp < ans) {
    ans = tmp;
    ansPoints.clear();
  }
  if (tmp == ans) {
    ansPoints.push_back({x, y});
  }
}

void Check1() {
  const auto [x0, y0] = points[0];
  const auto [x1, y1] = points[1];
  const auto [x2, y2] = points[2];
  const auto [x3, y3] = points[3];

  int x = x0 + x1 + x2 + x3;
  int y = max(max(y0, y1), max(y2, y3));
  Update(x, y);
}

void Check2() {
  const auto [x0, y0] = points[0];
  const auto [x1, y1] = points[1];
  const auto [x2, y2] = points[2];
  const auto [x3, y3] = points[3];

  int x = max(x0, x1 + x2 + x3);
  int y = y0 + max(y1, max(y2, y3));
  Update(x, y);
}

void Check3() {
  const auto [x0, y0] = points[0];
  const auto [x1, y1] = points[1];
  const auto [x2, y2] = points[2];
  const auto [x3, y3] = points[3];

  int x = max(x0 + x3, x1 + x2 + x3);
  int y = max(y0 + max(y1, y2), y3);
  Update(x, y);
}

void Check4() {
  const auto [x0, y0] = points[0];
  const auto [x1, y1] = points[1];
  const auto [x2, y2] = points[2];
  const auto [x3, y3] = points[3];

  int x = max(x0 + x1 + x3, x0 + x2 + x3);
  int y = max(max(y0, y3), y1 + y2);
  Update(x, y);
}

void Check5() {  // 左右没有交集
  const auto [x0, y0] = points[0];
  const auto [x1, y1] = points[1];
  const auto [x2, y2] = points[2];
  const auto [x3, y3] = points[3];

  int x = max(x0, x2) + max(x1, x3);
  int y = max(y0 + y2, y1 + y3);
  Update(x, y);
}

void Check6() {  //
  const auto [x0, y0] = points[0];
  const auto [x1, y1] = points[1];
  const auto [x2, y2] = points[2];
  const auto [x3, y3] = points[3];

  int x = max(x0 + x1, max(x2 + x3, x1 + x2));
  int y = max(y0 + y2, max(y0 + y3, y1 + y3));
  Update(x, y);
}

void Check() {  //
  Check1();
  Check2();
  Check3();
  Check4();
  Check5();
  Check6();
}

void Dfs1(int p) {
  if (p == N) {
    Check();
    return;
  }
  // 原顺序
  Dfs1(p + 1);

  swap(points[p].first, points[p].second);
  Dfs1(p + 1);
  swap(points[p].first, points[p].second);
}

void Dfs0(int p) {
  if (p == N) {
    Dfs1(0);
    return;
  }
  for (int i = p; i < N; i++) {
    swap(points[p], points[i]);
    Dfs0(p + 1);
    swap(points[p], points[i]);
  }
}

void Solver() {  //
  points.resize(N);
  for (auto& p : points) {
    scanf("%d%d", &p.first, &p.second);
  }
  ans = INT_MAX;

  Dfs0(0);
  sort(ansPoints.begin(), ansPoints.end());
  ansPoints.erase(unique(ansPoints.begin(), ansPoints.end()), ansPoints.end());
  printf("%d\n", ans);
  for (auto [x, y] : ansPoints) {
    printf("%d %d\n", x, y);
  }
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*
4 5
5 4 
4 5 
16 1 

52
4_13
----- our output ---------
80
5_16
*/