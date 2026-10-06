/*
ID: tiankonguse
TASK: WardenEscape
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P1095
PATH: NOIP2007 普及组 T3
submission:
*/
#define TASK "WardenEscape"
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

const ll kMagicCost = 10;
const ll kMagicResume = 4;
const ll kMagicDistance = 60;
const ll kWalkSpeed = 17;
ll t = 0;  // 已经花费的时间，答案为 Yes 时输出
ll s = 0;  // 已经走的距离, 答案为 No 时输出
ll M, S, T;

bool Finish() {  // 时间不多了，或已经到达了
  if (T <= 0 || S <= 0) {
    return true;
  }
  return false;
}
void OneMagic(int checkZero = false) {
  if (Finish()) return;
  if (M == 6 || M == 8) {             // 2s: 60m > 34m
    if (T == 1 || S <= kWalkSpeed) {  // 只能走 17m
      ll useTime = 1;
      ll useDistance = useTime * kWalkSpeed;
      t += useTime;
      T -= useTime;
      s += useDistance;
      S -= useDistance;
    } else {  // 消耗2秒魔法，走60米
      ll useTime = 2;
      ll useDistance = kMagicDistance;
      t += useTime;
      T -= useTime;
      s += useDistance;
      S -= useDistance;
      M = (M + 4) % 10;
    }
    return;
  }
  if (M == 4 || M == 2) {                 // 3s: 60m > 51m
    if (T <= 2 || S <= 2 * kWalkSpeed) {  // 只能走 34m
      ll useTime = 1;
      ll useDistance = useTime * kWalkSpeed;
      t += useTime;
      T -= useTime;
      s += useDistance;
      S -= useDistance;
    } else {  // 消耗3秒魔法，走60米
      ll useTime = 3;
      ll useDistance = kMagicDistance;
      t += useTime;
      T -= useTime;
      s += useDistance;
      S -= useDistance;
      M = (M + 8) % 10;
    }
    return;
  }
}

void Solver() {  //
  scanf("%lld%lld%lld", &M, &S, &T);

  if (M % 2 == 1) {
    M--;  // 奇数剩余一个永远用不上
  }
  if (M >= 10) {  // 空余的魔法先用完
    ll useTime = min(M / kMagicCost, T);
    ll useDistance = useTime * kMagicDistance;
    if (useDistance >= S) {
      ll ansT = (S + kMagicDistance - 1) / kMagicDistance;
      printf("Yes\n");
      printf("%lld\n", ansT);  // ansT 就可以到达 S
      return;
    }
    M -= useTime * kMagicCost;
    t += useTime;
    T -= useTime;
    s += useDistance;
    S -= useDistance;
  }
  while (M > 0 && !Finish()) {
    OneMagic();
  }
  if (!Finish()) {  // 7s: 120m > 119m
    ll useTime = min(T / 7, S / 120);
    ll useDistance = useTime * 120;
    t += useTime * 7;
    T -= useTime * 7;
    s += useDistance;
    S -= useDistance;

    // 此时如果 T >= 7 && 走路需要至少 7 秒，则可以继续使用一轮魔法
    ll walkTime = (S + kWalkSpeed - 1) / kWalkSpeed;
    if (T >= 7 && walkTime >= 7) {
      ll useTime = 1;
      ll useDistance = useTime * 120;
      t += useTime * 7;
      T -= useTime * 7;
      s += useDistance;
      S -= useDistance;
    }
  }
  if (!Finish()) {  // 最后只有走路了
    ll useTime = min(T, (S + kWalkSpeed - 1) / kWalkSpeed);
    ll useDistance = useTime * kWalkSpeed;
    t += useTime;
    T -= useTime;
    s += useDistance;
    S -= useDistance;
  }

  if (S > 0) {
    printf("No\n");
    printf("%lld\n", s);
  } else {
    printf("Yes\n");
    printf("%lld\n", t);
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
