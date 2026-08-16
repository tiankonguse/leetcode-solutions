/*
ID: tiankonguse
TASK: Cycle
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P1050
PATH:
submission:
*/
#define TASK "Cycle"
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

struct BigNum {
  vector<ll> data;  // 逆序存储
  BigNum() {}
  BigNum(ll x) {
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
  BigNum& Smp(int minBit = 0) {
    while (minBit > 0 && data.size() > minBit) {
      data.pop_back();
    }
    while (data.size() > 1 && data.back() == 0) {
      data.pop_back();
    }
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
int K;
char buf[222];

// 1: 1, 1, 1, 1
// 2: 4, -1
// 3: 4 * 5 ^(k-1)
// 4: 2, 10, -1
// 5: 1, -1
// 6: 1, -1
// 7: 4, 4, 20, 4 * 5^(k-2)
// 8: 4, 20, 100, -1
// 9: 2 * 5^(k-1)
// 10: 1, -1
// 11: 1, 2 * 5^ k
// 12: 4, 20, -1
// 13: 4 * 5 ^(k-1)
// 14: 2, -1
// 15: 1, -1
// 16: 1, 5, 25, 125, -1
// 17: 4 * 5 ^(k-1)
// 18: 4, -1
// 19: 2 * 5^(k-1)
// 20: 1, -1

// 1: 1*1^k
// 11: 1, 2 * 5^ k
// 21: 1, 5*10^(k-2)
// 31: 1, 2*5^k
// 41: 1, 5, 25*10^(k-3)
// 51: 1, 2, 10^(k-2)
// 61: 1, 5*10^(k-1)

// 所有 3 后缀的，都是 4 * 5^(k-1)
// 所有 7 后缀的，7 是特例，其他的都是 4 * 5 ^(k-1)
// 所有 9 后缀的，都是 2 * 5^(k-1)

string ToString(BigNum n, int k) {
  n.Smp(k);
  return n.ToString();
}

BigNum preLoopNum;  // 初始值 1
BigNum preLoopVal;  // 初始值 n, 代表 n^preLoopNum
ll TrySolver(const BigNum& nk, const int k) {
  unordered_map<string, int> mp;
  const string oneString = ToString(nk, k);
  MyPrintf("nk = %s k=%d oneString=%s\n", nk.ToString().c_str(), k, oneString.c_str());
  MyPrintf("preLoopNum = %s\n", preLoopNum.ToString().c_str());
  MyPrintf("preLoopVal = %s\n", preLoopVal.ToString().c_str());
  BigNum val(1);
  for (ll times = 1; times <= 11; times++) {  // 最多 10 次
    BigNum nextVal = val * preLoopVal;
    nextVal.Smp(K);
    const string s = ToString(nextVal, k);
    MyPrintf("times = %lld, val = %s\n", times, s.c_str());
    if (mp.count(s)) {
      if (mp[s] == 1) {
        string tmpString = ToString(val * nk, k);
        if (tmpString == oneString) {
          preLoopVal = val;
          preLoopNum = preLoopNum * BigNum(times - 1);
          return 0;
        } else {
          return -1;
        }
      } else {
        return -1;
      }
      break;
    }
    val = nextVal;
    mp[s] = times;
  }
  return -1;
}
inline BigNum Pow(BigNum a, ll b) {
  BigNum c(1);
  while (b != 0) {
    if (b & 1) {
      c = c * a;
    }
    a = a * a;
    b >>= 1;
  }
  return c;
}
void TryGreedy(string s) {
  if (s.back() == '3') {
    BigNum four(4);
    BigNum five(5);
    BigNum result = four * Pow(five, K - 1);
    printf("%s\n", result.ToString().c_str());
    return;
  }
  if (s.back() == '7') {
    if (s.size() == 1) {
      if (K == 1) {
        printf("4\n");
      } else {
        BigNum four(4);
        BigNum five(5);
        BigNum result = four * Pow(five, K - 2);
        printf("%s\n", result.ToString().c_str());
      }
    } else {
      BigNum four(4);
      BigNum five(5);
      BigNum result = four * Pow(five, K - 1);
      printf("%s\n", result.ToString().c_str());
    }
    return;
  }
  if (s.back() == '9') {
    BigNum two(2);
    BigNum five(5);
    BigNum result = two * Pow(five, K - 1);
    printf("%s\n", result.ToString().c_str());
    return;
  }
}

void SolverEx() {
  scanf("%s%d", buf, &K);
  string s = buf;
  BigNum n(s);
  n.Smp(K);

  preLoopNum = BigNum(1);
  preLoopVal = n;
  for (int k = 1; k <= K; k++) {
    if (TrySolver(n, k) == -1) {
      printf("-1\n");
      return;
    }
    MyPrintf("k = %d, preLoopNum = %s\n", k, preLoopNum.ToString().c_str());
  }
  TryGreedy(s);
  printf("%s\n", preLoopNum.ToString().c_str());
}

void Solver() {  //
  while (1) {
    SolverEx();  //
    // break;
  }
  return;
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
