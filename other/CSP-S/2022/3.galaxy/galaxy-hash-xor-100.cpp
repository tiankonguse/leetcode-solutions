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
#ifdef USACO_LOCAL_JUDGE
int debug_log = 0;
int debug_assert = 1;
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

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
// 2: 45
#define TASKNO "4"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

struct P2 {
  int n;
  vector<ll> scores;
  vector<int> inDegBase;    // 每个顶点入度的个数, 原始数据，不会修改
  vector<ll> inDegSum;      // 每个顶点入度的顶点和
  vector<ll> inDegSumBase;  // 每个顶点入度的顶点和, 原始数据，不会修改
  vector<int> inDeg;        // 每个顶点入度的个数, 最准确的，实时更新
  int edgeNum = 0;          // 有效边的个数, 最准确的，实时更新
  ll allScore = 0;
  ll allScoreBase = 0;

  void AddEdge(int u, int v) {
    MyPrintf("AddEdge %d %d\n", u, v);
    inDeg[v]++;
    edgeNum++;
    inDegSum[v] ^= scores[u];
    allScore ^= scores[u];
  }

  void DelEdge(int u, int v) {
    MyPrintf("DelEdge %d %d\n", u, v);
    inDeg[v]--;
    edgeNum--;
    inDegSum[v] ^= scores[u];
    allScore ^= scores[u];
  }
  void DelAllInEdge(int v) {
    edgeNum -= inDeg[v];
    inDeg[v] = 0;
    allScore ^= inDegSum[v];
    inDegSum[v] = 0;
  }
  void AddAllInEdge(int v) {
    edgeNum += inDegBase[v] - inDeg[v];
    inDeg[v] = inDegBase[v];
    allScore ^= inDegSumBase[v] ^ inDegSum[v];
    inDegSum[v] = inDegSumBase[v];
  }

  void Init(int n) {
    this->n = n;
    scores.resize(n + 1);
    for (int i = 1; i <= n; i++) {
      scores[i] = uint32_t(rand());
      allScoreBase ^= scores[i];
    }
    inDegSum.resize(n + 1, 0);
    inDegSumBase.resize(n + 1, 0);
    inDeg.resize(n + 1, 0);
    inDegBase.resize(n + 1, 0);
  }
  void ReadEdge(int u, int v) {
    inDeg[v]++;
    edgeNum++;
    inDegBase[v]++;
    inDegSum[v] ^= scores[u];
    inDegSumBase[v] ^= scores[u];
    allScore ^= scores[u];
  }
};

P2 p2;
int n, m, q;

void Solver() {  //

  srand(time(NULL));
  int u, v;
  scanf("%d%d", &n, &m);
  p2.Init(n);
  // p1.Init(n);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &u, &v);
    p2.ReadEdge(u, v);
  }
  scanf("%d", &q);
  while (q--) {
    int t;
    scanf("%d", &t);
    if (t == 1) {  // 删除 u->v
      scanf("%d%d", &u, &v);
      p2.DelEdge(u, v);
    } else if (t == 2) {
      scanf("%d", &v);
      p2.DelAllInEdge(v);
    } else if (t == 3) {
      scanf("%d%d", &u, &v);
      p2.AddEdge(u, v);
    } else {
      scanf("%d", &v);
      p2.AddAllInEdge(v);
    }

    if (p2.edgeNum == n && p2.allScore == p2.allScoreBase) {
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