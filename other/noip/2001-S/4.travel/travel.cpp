/*
ID: tiankonguse
TASK: travel
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P1027
PATH:
submission:
*/
#define TASK "travel"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  // 获取当前文件的完整路径
  string filePath = __FILE__;
  // 从路径中提取文件名（包含扩展名）
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  // 提取文件名（不包含扩展名）
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  // 检查文件名是否与预定义的 TASK 和 TASKEX 匹配
  assert(fileName == TASK TASKEX);
#endif
}

#ifdef USACO_LOCAL_JUDGE
int debug_log = 0;
int debug_assert = 0;
#define MyPrintf(...)                   \
  do {                                  \
    if (debug_log) printf(__VA_ARGS__); \
  } while (0)

#define MyAssert(...)                      \
  do {                                     \
    if (debug_assert) assert(__VA_ARGS__); \
  } while (0)
#else
#define MyPrintf(...)
#define MyAssert(...)
#endif

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

void InitIO(int fileIndex) {  //
// #define LOCAL_IO 1
#ifdef USACO_LOCAL_JUDGE
#define MAX_TIME 2000
#ifdef LOCAL_IO
#define USACO_TASK_FILE 2
// #define TASKNO 20
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
#endif
}

int T;
int n, price, A, B;
vector<pair<int, int>> points;
vector<vector<pair<int, double>>> g;
// 判断三个点是否可以组成直角三角形，其中 p1 是直角顶点
bool Check(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
  int dx1 = p2.first - p1.first, dy1 = p2.second - p1.second;
  int dx2 = p3.first - p1.first, dy2 = p3.second - p1.second;
  return dx1 * dx2 + dy1 * dy2 == 0;
}

// 输入矩阵三个顶点，三个顶点乱序输入，返回第四个顶点
pair<int, int> GetLastPoint(int x1, int y1, int x2, int y2, int x3, int y3) {
  vector<pair<int, int>> points;
  points.push_back({x1, y1});
  points.push_back({x2, y2});
  points.push_back({x3, y3});
  for (int i = 0; i < 3; i++) {  // 枚举直角顶点
    int i0 = i, i1 = (i + 1) % 3, i2 = (i + 2) % 3;
    if (Check(points[i0], points[i1], points[i2])) {
      return {points[i1].first + points[i2].first - points[i0].first,
              points[i1].second + points[i2].second - points[i0].second};
    }
  }
  return {0, 0};
}

double GetDis(pair<int, int> p1, pair<int, int> p2) {
  return sqrt(1.0 * (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}

double Dijkstra(int s, const int t, const vector<vector<pair<int, double>>>& S) {
  int n = S.size();
  vector<double> dist(n, INFL);
  dist[s] = 0;
  priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pque;
  pque.push({0, s});
  while (!pque.empty()) {
    const auto [d, u] = pque.top();
    pque.pop();
    if (dist[u] < d) continue;
    if (u == t) continue;
    for (const auto [v, cost] : S[u]) {
      if (dist[v] > dist[u] + cost) {
        dist[v] = dist[u] + cost;
        pque.push({dist[v], v});
      }
    }
  }
  return dist[t];
}

void Solver() {  //
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n, &price, &A, &B);
    A--, B--;
    points.clear();
    g.clear();
    g.resize(4 * n + 2);
    int va = 4 * n, vb = 4 * n + 1;
    for (int i = 0; i < n; i++) {
      int x1, y1, x2, y2, x3, y3, cityPrice;
      scanf("%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &cityPrice);
      auto [x4, y4] = GetLastPoint(x1, y1, x2, y2, x3, y3);
      points.push_back({x1, y1});
      points.push_back({x2, y2});
      points.push_back({x3, y3});
      points.push_back({x4, y4});

      int pn = points.size();
      int u0 = pn - 4;
      for (int u = u0; u < pn; u++) {
        for (int v = 0; v < u0; v++) {
          double dis = GetDis(points[u], points[v]) * price;
          g[u].push_back({v, dis});
          g[v].push_back({u, dis});
        }
        for (int v = u + 1; v < pn; v++) {
          double dis = GetDis(points[u], points[v]) * cityPrice;
          g[u].push_back({v, dis});
          g[v].push_back({u, dis});
        }
      }
      if (i == A) {
        for (int u = u0; u < pn; u++) {
          g[va].push_back({u, 0});
          g[u].push_back({va, 0});
        }
      }
      if (i == B) {
        for (int u = u0; u < pn; u++) {
          g[vb].push_back({u, 0});
          g[u].push_back({vb, 0});
        }
      }
    }
    printf("%.1f\n", Dijkstra(va, vb, g));
  }
}

#ifdef USACO_LOCAL_JUDGE
double costTime = 0;
#endif
void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  costTime = my.count();
#ifndef USACO_TASK_FILE
  printf("my 用时: %.0lfms\n", costTime);
#endif
#endif
}

#ifdef USACO_TASK_FILE
#include <unistd.h>

#include <cstdio>
int AC = 0;
void DiffAns(int stdout_fd, int i) {
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  int fileIndex = i;
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileAns = string(TASK) + to_string(fileIndex) + ".ans";
  string fileOut = string(TASK) + to_string(fileIndex) + ".out";
  string cmd = string("diff -w " + fileAns + " " + fileOut + " > /dev/null");
  if (system(cmd.c_str())) {
    printf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
  } else {
    if (costTime > MAX_TIME) {
      printf("case %d: Time Limit Exceeded, cost %.0lfms\n", i, costTime);
    } else {
      AC++;
      printf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
}
void DiffSummary(int stdout_fd) {  // 统计通过的用例数量和得分
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  printf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
}
#endif
int main(int argc, char** argv) {
  CheckUsacoTask();
  int fileIndex = 1;
#ifdef USACO_TASK_FILE
  // 保存当前的 stdout 文件指针
  int stdout_fd = dup(STDOUT_FILENO);
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    fileIndex = i;
#endif
    InitIO(fileIndex);
    ExSolver();
#ifdef USACO_TASK_FILE
    fclose(stdout);
    DiffAns(stdout_fd, i);
    stdout_fd = dup(STDOUT_FILENO);
  }
  DiffSummary(stdout_fd);
#endif
  return 0;
}
