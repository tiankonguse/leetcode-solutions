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

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
// 2: 45
#define TASKNO "4"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

// struct P1 {
//   int n;
//   vector<unordered_set<int>> rg;
//   vector<unordered_set<int>> rgDel;
//   vector<int> outDeg;   // 每个顶点出度的个数
//   vector<int> inDeg;    // 每个顶点入度的个数
//   int edgeNum = 0;      // 有效边的个数
//   vector<int> outStat;  // 出度统计

//   void Init(int n) {
//     this->n = n;
//     rg.resize(n + 1);
//     rgDel.resize(n + 1);
//     outDeg.resize(n + 1);
//     inDeg.resize(n + 1);
//     outStat.resize(n + 1);
//     outStat[0] = n;
//   }
//   void ReadEdge(int u, int v) {  //
//     AddEdge(u, v);
//   }

//   void AddEdge(int u, int v) {
//     rg[v].insert(u);
//     rgDel[v].erase(u);
//     outDeg[u]++;
//     inDeg[v]++;
//     edgeNum++;
//     outStat[outDeg[u] - 1]--;
//     outStat[outDeg[u]]++;
//   }
//   void DelEdge(int u, int v) {
//     rg[v].erase(u);
//     rgDel[v].insert(u);
//     outDeg[u]--;
//     inDeg[v]--;
//     edgeNum--;
//     outStat[outDeg[u] + 1]--;
//     outStat[outDeg[u]]++;
//   }
//   void DelAllInEdge(int v) {
//     while (!rg[v].empty()) {
//       int u = *rg[v].begin();
//       DelEdge(u, v);
//     }
//   }
//   void AddAllInEdge(int v) {
//     for (auto u : rgDel[v]) {
//       AddEdge(u, v);
//     }
//   }
//   bool Check() {  //
//     return edgeNum == n && outStat[1] == n;
//   }
// };
struct P2 {
  int n;
  vector<unordered_map<int, int>> rg;     // 懒标记
  vector<unordered_map<int, int>> rgDel;  // 懒标记
  vector<int> outDeg;                     // 每个顶点出度的个数, 懒标记
  vector<int> inDegBase;                  // 每个顶点入度的个数, 原始数据，不会修改
  vector<int> inDeg;                      // 每个顶点入度的个数, 最准确的，实时更新
  int edgeNum = 0;                        // 有效边的个数, 最准确的，实时更新
  vector<int> outStat;                    // 出度统计
  vector<int> lazyFlag;
  vector<int> opList;
  int opIndex = 0;
  int prePushIndex = 0;

  void realAddEdge(int u, int v, int force = 0) {
    if (!force) {
      MyAssert(rg[v].count(u) == 0);
      MyAssert(rgDel[v].count(u) > 0);
    }
    rg[v][u] = opIndex;
    rgDel[v].erase(u);
    outDeg[u]++;
    outStat[outDeg[u] - 1]--;
    outStat[outDeg[u]]++;
  }

  void realDelEdge(int u, int v) {
    MyAssert(rg[v].count(u) != 0);
    MyAssert(rgDel[v].count(u) == 0);
    rg[v].erase(u);
    rgDel[v][u] = opIndex;
    outDeg[u]--;
    outStat[outDeg[u] + 1]--;
    outStat[outDeg[u]]++;
  }

  void AddEdge(int u, int v) {
    MyPrintf("AddEdge %d %d\n", u, v);
    const int lazyIndex = lazyFlag[v];
    // MyAssert(lazyIndex == 0);
    // MyAssert(opList[lazyIndex] == 0);
    if (opList[lazyIndex] < 0) {
      // lazy 是全部删除，这里添加，说明是首次添加,需要标记起来
      inDeg[v]++;
      edgeNum++;
      if (rg[v].count(u) == 0) {
        // 删除，批量删除，添加
        realAddEdge(u, v);
      } else {
        // 添加，批量删除， 添加
        MyAssert(rg[v].count(u) > 0);
        rg[v][u] = opIndex;  // 已经在了，更新操作序号
      }
    } else if (opList[lazyIndex] > 0) {
      // lazy 是全部添加，这里添加，说明之前有单独删除过
      // 情况1: 删除, 全部添加, 删除, 添加, 此时 rg 为空
      // 情况2: 全部添加, 删除, 添加, 删除 此时 rg 为空
      MyAssert(rg[v].count(u) == 0);
      inDeg[v]++;
      edgeNum++;
      realAddEdge(u, v);
      // if (int(rg[v].size()) == inDegBase[v]) {
      //   lazyFlag[v] = 0;
      // }
    } else {
      inDeg[v]++;
      edgeNum++;
      realAddEdge(u, v);
    }
  }

  void DelEdge(int u, int v) {
    MyPrintf("DelEdge %d %d\n", u, v);
    const int lazyIndex = lazyFlag[v];
    // MyAssert(lazyIndex == 0);
    // MyAssert(opList[lazyIndex] == 0);
    if (opList[lazyIndex] < 0) {  //
      // lazy 是全部删除，再次删除，说明中间有单点添加，rg 肯定存在
      MyAssert(rg[v].count(u) > 0);
      inDeg[v]--;
      edgeNum--;
      realDelEdge(u, v);
      // if (rg[v].empty()) {
      //   lazyFlag[v] = 0;  // 全部删除，已经全部删除了
      // }
    } else if (opList[lazyIndex] > 0) {
      // 可能是首次添加，也可能是中途有删除在增加
      // 情况1: 全部添加,删除, 此时 rg 非空
      // 情况2: 删除,全部添加,删除, 此时 rg 为空
      // 情况3: 全部添加, 删除,添加,删除, 此时 rg 非空
      inDeg[v]--;
      edgeNum--;
      if (rg[v].count(u) > 0) {
        realDelEdge(u, v);
      } else {
        MyAssert(rgDel[v].count(u) > 0);
        rgDel[v][u] = opIndex;
      }
    } else {
      inDeg[v]--;
      edgeNum--;
      realDelEdge(u, v);
    }
  }
  void DelAllInEdge(int v) {
    MyPrintf("DelAllInEdge %d inDeg=%d lazyFlag=%d inDegBase=%d\n", v, inDeg[v], lazyFlag[v], inDegBase[v]);
    opList[opIndex] = -v;
    edgeNum -= inDeg[v];
    inDeg[v] = 0;
    lazyFlag[v] = opIndex;
  }
  void AddAllInEdge(int v) {
    MyPrintf("AddAllInEdge %d inDeg=%d lazyFlag=%d inDegBase=%d\n", v, inDeg[v], lazyFlag[v], inDegBase[v]);
    opList[opIndex] = v;
    edgeNum += inDegBase[v] - inDeg[v];
    inDeg[v] = inDegBase[v];
    lazyFlag[v] = opIndex;
  }

  void PushLazyFlag() {  //
    // MyAssert(prePushIndex + 1 == opIndex);
    for (int i = prePushIndex + 1; i <= opIndex; i++) {
      int signVal = opList[i];
      int v = abs(signVal);
      if (v == 0) continue;            // 不是批量操作
      if (i != lazyFlag[v]) continue;  // 不是最后一个批量操作，不需要处理
      if (signVal > 0) {               // 全部添加
        for (auto it = rgDel[v].begin(); it != rgDel[v].end();) {
          auto tmpIt = it;
          it++;
          int u = tmpIt->first;
          MyAssert(rg[v].count(u) == 0);
          // MyAssert(tmpIt->second <= i);
          if (tmpIt->second > i) continue;  // 之后又删除
          realAddEdge(u, v);
        }
        lazyFlag[v] = 0;
      } else {
        //   if (lazyFlag[v] == 0) continue;
        for (auto it = rg[v].begin(); it != rg[v].end();) {
          auto tmpIt = it;
          it++;
          int u = tmpIt->first;
          MyAssert(rgDel[v].count(u) == 0);
          // MyAssert(tmpIt->second <= i);
          if (tmpIt->second > i) continue;  // 之后又添加的
          realDelEdge(u, v);
        }
        lazyFlag[v] = 0;
      }
    }
    prePushIndex = opIndex;
  }
  void Init(int n) {
    this->n = n;
    rg.resize(n + 1);
    rgDel.resize(n + 1);
    outDeg.resize(n + 1, 0);
    inDeg.resize(n + 1, 0);
    inDegBase.resize(n + 1, 0);
    outStat.resize(n + 1, 0);
    lazyFlag.resize(n + 1, 0);
    outStat[0] = n;
  }
  void ReadEdge(int u, int v) {
    inDeg[v]++;
    edgeNum++;
    inDegBase[v]++;
    realAddEdge(u, v, 1);
  }
  void InitOpLint(int q) {  //
    opList.resize(q + 1, 0);
  }
  void AddOpIndex() {  //
    opIndex++;
  }
};

// P1 p1;
P2 p2;
int n, m, q;

// void DiffP1AndP2() {
//   for (int i = 1; i <= n; i++) {
//     MyAssert(p1.rg[i].size() == p2.rg[i].size());
//     MyAssert(p1.rgDel[i].size() == p2.rgDel[i].size());
//     MyAssert(p1.outDeg[i] == p2.outDeg[i]);
//     MyAssert(p1.inDeg[i] == p2.inDeg[i]);
//     MyAssert(p1.outStat[i] == p2.outStat[i]);
//   }
// }

void Solver() {  //
  int u, v;
  scanf("%d%d", &n, &m);
  p2.Init(n);
  // p1.Init(n);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &u, &v);
    // p1.ReadEdge(u, v);
    p2.ReadEdge(u, v);
  }
  scanf("%d", &q);
  p2.InitOpLint(q);
  while (q--) {
    p2.AddOpIndex();
    int t;
    scanf("%d", &t);
    if (t == 1) {  // 删除 u->v
      scanf("%d%d", &u, &v);
      p2.DelEdge(u, v);
      // p1.DelEdge(u, v);
    } else if (t == 2) {
      scanf("%d", &v);
      p2.DelAllInEdge(v);
      // p1.DelAllInEdge(v);
    } else if (t == 3) {
      scanf("%d%d", &u, &v);
      p2.AddEdge(u, v);
      // p1.AddEdge(u, v);
    } else {
      scanf("%d", &v);
      p2.AddAllInEdge(v);
      // p1.AddAllInEdge(v);
    }

    if (p2.edgeNum == n) {
      p2.PushLazyFlag();
      // DiffP1AndP2();
      if (p2.outStat[1] == n) {
        printf("YES\n");
      } else {
        printf("NO\n");
      }
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