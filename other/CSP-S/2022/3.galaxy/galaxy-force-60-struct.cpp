/*
ID: tiankonguse
TASK: galaxy
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P8819
PATH: P8819 [CSP-S 2022] 星战
submission: https://www.luogu.com.cn/record/221090559
评测分数: 60
*/
#define TASK "galaxy"
#define TASKEX "-force-60-struct"

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

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "4"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

struct P1 {
  int n;
  vector<unordered_set<int>> rg;
  vector<unordered_set<int>> rgDel;
  vector<int> outDeg;   // 每个顶点出度的个数
  vector<int> inDeg;    // 每个顶点入度的个数
  int edgeNum = 0;      // 有效边的个数
  vector<int> outStat;  // 出度统计

  void Init(int n) {
    this->n = n;
    rg.resize(n + 1);
    rgDel.resize(n + 1);
    outDeg.resize(n + 1);
    inDeg.resize(n + 1);
    outStat.resize(n + 1);
    outStat[0] = n;
  }
  void ReadEdge(int u, int v) {  //
    AddEdge(u, v);
  }

  void AddEdge(int u, int v) {
    rg[v].insert(u);
    rgDel[v].erase(u);
    outDeg[u]++;
    inDeg[v]++;
    edgeNum++;
    outStat[outDeg[u] - 1]--;
    outStat[outDeg[u]]++;
  }
  void DelEdge(int u, int v) {
    rg[v].erase(u);
    rgDel[v].insert(u);
    outDeg[u]--;
    inDeg[v]--;
    edgeNum--;
    outStat[outDeg[u] + 1]--;
    outStat[outDeg[u]]++;
  }
  void DelAllInEdge(int v) {
    while (!rg[v].empty()) {
      int u = *rg[v].begin();
      DelEdge(u, v);
    }
  }
  void AddAllInEdge(int v) {
    for (auto u : rgDel[v]) {
      AddEdge(u, v);
    }
  }
  bool Check() {  //
    return edgeNum == n && outStat[1] == n;
  }
};

P1 p1;
int n, m, q;
void Solver() {  //
  scanf("%d%d", &n, &m);
  p1.Init(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    p1.ReadEdge(u, v);
  }
  scanf("%d", &q);
  while (q--) {
    int t;
    scanf("%d", &t);
    if (t == 1) {  // 删除 u->v
      int u, v;
      scanf("%d%d", &u, &v);
      p1.DelEdge(u, v);
    } else if (t == 2) {
      int v;
      scanf("%d", &v);
      p1.DelAllInEdge(v);
    } else if (t == 3) {
      int u, v;
      scanf("%d%d", &u, &v);
      p1.AddEdge(u, v);
    } else {
      int v;
      scanf("%d", &v);
      p1.AddAllInEdge(v);
    }

    if (p1.Check()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/