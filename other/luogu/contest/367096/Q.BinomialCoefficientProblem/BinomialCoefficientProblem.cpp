/*
ID: tiankonguse
TASK: BinomialCoefficientProblem
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P2822?contestId=367096
PATH: P2822 [NOIP 2016 提高组] 组合数问题
submission:
*/
#define TASK "BinomialCoefficientProblem"
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
#define USACO_TASK_FILE 0
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

// 埃氏筛求 N 范围内的所有质数
/*
1e4 3.732020845644619
1e5 4.053948940531981
1e6 4.316983346365776
1e7 4.539375767702223
*/
const int N = 30;
const int M = 30;
bool is[N];
int prm[M];
int prmCnt = 0;
int InitPrimes() {
  // O(n log log n)
  if (prmCnt > 0) return prmCnt;
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  memset(is, 1, sizeof(is));
  prm[k++] = 2;
  is[0] = is[1] = 0;
  for (i = 4; i < N; i += 2) is[i] = 0;
  for (i = 3; i < e; i += 2) {
    if (is[i]) {
      prm[k++] = i;
      for (int j = i * i; j < N; j += i * 2) {
        is[j] = 0;
      }
    }
  }
  for (; i < N; i += 2) {
    if (is[i]) {
      prm[k++] = i;
    }
  }
  return prmCnt = k;
}
int maxN = 2010;

vector<pair<int, int>> primeK;
map<int, int> primeKH;
int kn;
void InitK(ll v) {
  for (int i = 0; i < prmCnt && v > 1; i++) {
    if (v % prm[i] != 0) continue;
    while (v % prm[i] == 0) {
      primeKH[prm[i]]++;
      v /= prm[i];
    }
  }
  if (v > 1) {
    primeKH[v]++;
  }
  for (auto [v, num] : primeKH) {
    primeK.push_back({v, num});
  }
  kn = primeKH.size();
}

vector<array<int, 2>> nums;
void InitNM(ll v) {
  auto& ans = nums[v];
  for (int i = 0; i < prmCnt && v > 1; i++) {
    while (v % prm[i] == 0) {
      for (int x = 0; x < kn; x++) {
        if (primeK[x].first == prm[i]) {
          ans[x]++;
        }
      }
      v /= prm[i];
    }
  }
  if (v > 1) {
    for (int x = 0; x < kn; x++) {
      if (primeK[x].first == v) {
        ans[x]++;
      }
    }
  }
}

vector<vector<array<int, 2>>> C;
vector<vector<ll>> g;
void InitC() {
  C.resize(maxN, vector<array<int, 2>>(maxN));
  g.resize(maxN, vector<ll>(maxN, 0));
  for (int i = 2; i < maxN; i++) {
    for (int j = 1; j <= i; j++) {
      // C(i,j) = i! / (j! * (i-j)!)
      auto& Cij = C[i][j];
      Cij = C[i][j - 1];
      const auto& up = nums[i - j + 1];
      const auto& down = nums[j];
      for (int x = 0; x < kn; x++) {
        Cij[x] += up[x];
        Cij[x] -= down[x];
      }
    }
  }

  for (int i = 1; i < maxN; i++) {
    for (int j = 1; j < maxN; j++) {
      auto& Cij = C[i][j];
      g[i][j] = g[i][j - 1] + g[i - 1][j] - g[i - 1][j - 1];
      int ok = true;
      for (int x = 0; x < kn; x++) {
        if (Cij[x] < primeK[x].second) {
          ok = false;
        }
      }
      if (ok) {
        g[i][j]++;
      }
    }
  }
}

int n, m, k;
void Init() {
  InitPrimes();
  InitK(k);
  nums.resize(maxN);
  for (int i = 2; i < maxN; i++) {
    InitNM(i);
  }
  InitC();
}

vector<pair<int, int>> querys;
void Solver() {  //
  int t;
  scanf("%d%d", &t, &k);
  querys.resize(t);
  maxN = 0;
  for (int i = 0; i < t; i++) {
    scanf("%d%d", &querys[i].first, &querys[i].second);
    querys[i].second = min(querys[i].second, querys[i].first);
    maxN = max(maxN, querys[i].first);
  }
  maxN++;
  MyPrintf("maxN = %d\n", maxN);
  Init();
  for (int i = 0; i < t; i++) {
    n = querys[i].first;
    m = querys[i].second;
    printf("%d\n", g[n][m]);
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
  auto my = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
  costTime = my.count();
#ifndef USACO_TASK_FILE
  MyPrintf("my 用时: %.0lfms\n", costTime);
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
    MyPrintf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
  } else {
    if (costTime > MAX_TIME) {
      MyPrintf("case %d: Time Limit Exceeded, cost %.0lfms\n", i, costTime);
    } else {
      AC++;
      MyPrintf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
}
void DiffSummary(int stdout_fd) {  // 统计通过的用例数量和得分
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  MyPrintf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
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
