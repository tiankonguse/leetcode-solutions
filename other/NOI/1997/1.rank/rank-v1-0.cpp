/*
ID: tiankonguse
TASK: rank
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "rank"
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

// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t);
  return y;
}

// 有符号分数 sign * A / B
struct Number {
  ll A;
  ll B;
  Number() {
    A = 0;
    B = 1;
  }
  Number(int a) {
    A = a;
    B = 1;
  }
  Number(ll a, ll b) {
    A = a;
    B = b;
    Normalize();
  }
  Number& operator=(const int other) {
    A = other;
    B = 1;
    return *this;
  }
  Number& operator+=(const Number& b) {
    Number& a = *this;
    a.A = a.A * b.B + b.A * a.B;
    a.B = a.B * b.B;
    Normalize();
    return *this;
  }
  Number& operator-=(const Number& b) {
    Number& a = *this;
    a.A = a.A * b.B - b.A * a.B;
    a.B = a.B * b.B;
    Normalize();
    return *this;
  }
  Number& operator*=(const Number& b) {
    Number& a = *this;
    a.A = a.A * b.A;
    a.B = a.B * b.B;
    Normalize();
    return *this;
  }

  Number& operator/=(const Number& b) {
    Number& a = *this;
    a.A = a.A * b.B;
    a.B = a.B * b.A;
    Normalize();
    return *this;
  }
  bool operator==(const Number& b) const {
    const Number& a = *this;
    return a.A == b.A && a.B == b.B;
  }
  bool operator!=(const Number& b) const { return !(*this == b); }
  bool operator<(const Number& b) const {
    const Number& a = *this;
    return a.A * b.B < b.A * a.B;
  }
  bool operator>(const Number& b) const {
    const Number& a = *this;
    return a.A * b.B > b.A * a.B;
  }

  Number Abs() const {
    Number ret;
    ret.A = abs(A);
    ret.B = B;
    return ret;
  }
  void Normalize() {
    if (A == 0) {
      B = 1;
      return;
    }
    int sign = 1;
    if (A < 0) {
      sign = -1;
      A = -A;
    }
    ll g = Gcd(A, B);
    A /= g;
    B /= g;
    A *= sign;
  }
};

Number operator+(const Number& a, const Number& b) {
  Number ret = a;
  ret += b;
  return ret;
}
Number operator-(const Number& a, const Number& b) {
  Number ret = a;
  ret -= b;
  return ret;
}
Number operator*(const Number& a, const Number& b) {
  Number ret = a;
  ret *= b;
  return ret;
}
Number operator/(const Number& a, const Number& b) {
  Number ret = a;
  ret /= b;
  return ret;
}

int n;
vector<vector<Number>> X, Y;
vector<Number> avg, sumX, sumY, xAvg;
void Solver() {  //
  scanf("%d", &n);
  const Number N = Number(n);

  X.resize(n, vector<Number>(8));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 8; j++) {
      ll x;
      scanf("%lld", &x);
      X[i][j] = x;
    }
  }
  // 计算竞赛的平均分
  avg.resize(8);
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < n; i++) {
      avg[j] += X[i][j];
    }
    avg[j] /= N;
  }

  // 计算选手的总分
  sumX.resize(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 8; j++) {
      sumX[i] += X[i][j];
    }
  }

  // 竞赛的位置分
  xAvg.resize(8);
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < n; i++) {
      xAvg[j] += (X[i][j] - avg[j]).Abs();
    }
    xAvg[j] /= N;
  }

  Y.resize(n, vector<Number>(8));
  for (int j = 0; j < 8; j++) {
    if (xAvg[j].A == 0) continue;
    for (int i = 0; i < n; i++) {
      Y[i][j] = (X[i][j] - avg[j]) / xAvg[j];
    }
  }

  // 总位置分
  sumY.resize(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      sumY[i] += Y[i][j];
    }
    for (int j = 3; j < 8; j++) {
      sumY[i] += Y[i][j] * Number(8, 10);
    }
  }

  vector<int> rank(n);
  for (int i = 0; i < n; i++) {
    rank[i] = i;
  }
  sort(rank.begin(), rank.end(), [&](int a, int b) {
    // 优先按照总位置分排序
    if (sumY[a] != sumY[b]) {
      return sumY[a] > sumY[b];
    }
    // 如果总位置分相同，按照总分排序
    if (sumX[a] != sumX[b]) {
      return sumX[a] > sumX[b];
    }
    // 最后编号在前的选手名次在前
    return a < b;
  });
  for (int i = 0; i < n; i++) {
    printf("%d\n", rank[i] + 1);
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