/*
ID: tiankonguse
TASK: individual-income-tax
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "individual-income-tax"
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
// #define LOCAL_IO 0
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

int m;
vector<vector<double>> g;
double AddInCome(double money) {
  /*
  每次不超过 4000 元的，减除费用 800 元；4000 元以上的，减除 20% 的费用，余额为应纳税所得额
  级数	每次应纳税所得额	税率
  1	不超过 20000 元的部分	20%
  2	20000∼50000 元的部分	30%
  3	超过 50000 元的部分	40%
  */
  double taxable = money;
  if (money <= 4000) {
    taxable -= 800;
  } else {
    taxable -= money * 0.2;
  }
  if (taxable <= 0) return 0;
  double tax = 0;
  if (taxable <= 20000) {
    tax = taxable * 0.2;
  } else if (taxable <= 50000) {
    tax = 20000 * 0.2 + (taxable - 20000) * 0.3;
  } else {
    tax = 20000 * 0.2 + 30000 * 0.3 + (taxable - 50000) * 0.4;
  }
  return tax;
}

vector<tuple<ll, ll, ll, double>> payTables;  // <left, right, preTax, rate>
void InitPay() {
  if (!payTables.empty()) return;
  ll baseTax = 0;
  payTables.push_back(make_tuple(0, 500, baseTax, 0.05));
  baseTax += 500 * 0.05;
  payTables.push_back(make_tuple(500, 2000, baseTax, 0.1));
  baseTax += (2000 - 500) * 0.1;
  payTables.push_back(make_tuple(2000, 5000, baseTax, 0.15));
  baseTax += (5000 - 2000) * 0.15;
  payTables.push_back(make_tuple(5000, 20000, baseTax, 0.2));
  baseTax += (20000 - 5000) * 0.2;
  payTables.push_back(make_tuple(20000, 40000, baseTax, 0.25));
  baseTax += (40000 - 20000) * 0.25;
  payTables.push_back(make_tuple(40000, 60000, baseTax, 0.3));
  baseTax += (60000 - 40000) * 0.3;
  payTables.push_back(make_tuple(60000, 80000, baseTax, 0.35));
  baseTax += (80000 - 60000) * 0.35;
  payTables.push_back(make_tuple(80000, 100000, baseTax, 0.4));
  baseTax += (100000 - 80000) * 0.4;
  payTables.push_back(make_tuple(100000, INF, baseTax, 0.45));
}

double AddPay(ll money) {
  /*
    工资、薪金所得，按月计算征税，以每月收入额减除费用 800 元后的余额作为该月应纳税所得额，税率如下表所示：
    级数	月应纳税所得额	税率
    1	不超过 500 元的部分	5%
    2	500∼2000 元的部分	10%
    3	2000∼5000 元的部分	15%
    4	5000∼20000 元的部分	20%
    5	20000∼40000 元的部分	25%
    6	40000∼60000 元的部分	30%
    7	60000∼80000 元的部分	35%
    8	80000∼100000 元的部分	40%
    9	超过 100000 元的部分	45%
  */
  InitPay();
  ll taxable = money - 800;
  if (taxable <= 0) return 0;
  for (auto [left, right, preTax, rate] : payTables) {
    if (taxable <= right) {
      return preTax + (taxable - left) * rate;
    }
  }
  return 0;
}

void Solver() {  //
  scanf("%d", &m);
  g.resize(12, vector<double>(m, 0.0));

  double ans = 0;

  while (1) {
    char op[20];
    scanf("%s", op);
    if (op[0] == '#') {
      break;
    }
    ll num, month, day, money;
    scanf("%lld %lld/%lld %lld", &num, &month, &day, &money);
    if (op[0] == 'P') {  // PAY 工资
      g[month - 1][num - 1] += money;
    } else {  // INCOME 一次性收入
      ans += AddInCome(money);
    }
  }
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < m; j++) {
      ans += AddPay(g[i][j]);
    }
  }
  printf("%.2f\n", ans);
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
