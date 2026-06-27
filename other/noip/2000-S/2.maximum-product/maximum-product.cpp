/*
ID: tiankonguse
TASK: maximum-product
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P1018
PATH:
submission:
*/
#define TASK "maximum-product"
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

struct BigNum {
  vector<ll> data;  // 逆序存储
  BigNum(ll x = 0) {
    while (x) {
      data.push_back(x % 10);
      x /= 10;
    }
    if (data.empty()) {
      data.push_back(0);
    }
  }
  BigNum(const string& s) {
    for (int i = s.size() - 1; i >= 0; i--) {
      data.push_back(s[i] - '0');
    }
  }
  BigNum& Smp() {
    while (data.size() > 1 && data.back() == 0) {
      data.pop_back();
    }
    return *this;
  }
  BigNum& Append(ll x) { // 不能删除前导0
    data.push_back(x);
    return *this;
  }
  BigNum operator*(const BigNum& other) const {
    BigNum res;
    res.data.resize(data.size() + other.data.size() + 1, 0);
    for (int i = 0; i < data.size(); i++) {
      int carry = 0;
      int pos = i;
      for (int j = 0; j < other.data.size(); j++) {
        res.data[pos] += data[i] * other.data[j] + carry;
        carry = res.data[pos] / 10;
        res.data[pos] %= 10;
        pos++;
      }
      while (carry) {
        res.data[pos] += carry;
        carry = res.data[pos] / 10;
        res.data[pos] %= 10;
        pos++;
      }
    }
    return res.Smp();
  }
  bool operator<(const BigNum& other) const {
    if (data.size() != other.data.size()) {
      return data.size() < other.data.size();
    }
    for (int i = data.size() - 1; i >= 0; i--) {
      if (data[i] != other.data[i]) {
        return data[i] < other.data[i];
      }
    }
    return false;
  }
  string ToString() const {
    string res;
    for (int i = data.size() - 1; i >= 0; i--) {
      res.push_back(data[i] + '0');
    }
    return res;
  }
};

char s[100];
string S;

BigNum dp[50][10];
bool dpFlag[50][10];

// 前 p 个数字，分割为 k 个数字的最大乘积
BigNum& Dfs(const int p, const int k) {
  if (dpFlag[p][k]) {
    return dp[p][k];
  }
  dpFlag[p][k] = true;
  BigNum& ans = dp[p][k];
  if (k == 1) {
    ans = BigNum(S.substr(0, p));
    MyPrintf("p=%d k=%d ans=%s substr=%s\n", p, k, ans.ToString().c_str(), S.substr(0, p).c_str());
    return ans;
  }
  // 枚举最后一个数字的长度
  ans = BigNum(0);
  BigNum now;
  now.data.clear();  // 后面会单独从低位到高位一个个插入
  int pi = p;
  while (pi >= k) {
    now.Append(S[pi - 1] - '0');
    const BigNum& next = Dfs(pi - 1, k - 1);
    BigNum newAns = next * now;
    MyPrintf("p=%d k=%d pi=%d next=%s now=%s newAns=%s\n", p, k, pi, next.ToString().c_str(), now.ToString().c_str(),
             newAns.ToString().c_str());
    if (ans < newAns) {
      ans = newAns;
    }
    pi--;
  }
  MyPrintf("p=%d k=%d ans=%s\n", p, k, ans.ToString().c_str());
  return ans;
}

void Solver() {  //
  int N, K;
  scanf("%d%d", &N, &K);
  scanf("%s", s);
  S = s;
  memset(dpFlag, 0, sizeof(dpFlag));
  BigNum& ans = Dfs(N, K + 1);
  printf("%s\n", ans.ToString().c_str());
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
