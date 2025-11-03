/*
ID: tiankonguse
TASK: employ
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "employ"
#define TASKEX "-v4"

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
#ifdef LOCAL_IO
#define USACO_TASK_FILE 0
#define TASKNO 1
#ifndef USACO_TASK_FILE
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
#endif
}

int n, m;
char S[555];
vector<int> C;
vector<int> P;  // 排列，标记是否选择

ll ans = 0;

namespace DP_ALL_S1 {
struct mint {
  const ll mod = 998244353;
  ll x;
  mint(ll x = 0) : x(x) {}
  mint operator+(const ll& b) const { return mint((x + b) % mod); }
  mint operator+(const mint& b) const { return mint((x + b.x) % mod); }
  mint& operator+=(const ll& b) { return (x = (x + b) % mod), *this; }
  mint& operator+=(const mint& b) { return (x = (x + b.x) % mod), *this; }
  mint operator*(const ll& b) const { return mint((x * b) % mod); }
  mint operator*(const mint& b) const { return mint((x * b.x) % mod); }
  mint& operator*=(const ll& b) { return (x = (x * b) % mod), *this; }
  mint& operator*=(const mint& b) { return (x = (x * b.x) % mod), *this; }
  mint& operator=(const mint& b) { return (x = b.x), *this; }
  mint& operator=(const ll& b) { return (x = b), *this; }
  bool operator==(const ll& b) const { return x == b; }
  bool operator==(const mint& b) const { return x == b.x; }
};

vector<int> bucket;               // SC 后缀和
vector<int> SC;                   // SC 后缀和
vector<vector<vector<mint>>> dp;  // 前 i 个人，挂了j个，其中前 i 个人中忍耐度大于 j 的有 k 个

ll Ranges(int l, int r) {
  if (l > n) return 0;
  if (r > n) r = n;
  return SC[l] - SC[r + 1];
}

ll Solver(int m) {
  bucket.clear();
  bucket.resize(n + 2, 0);
  for (int i = 1; i <= n; i++) {
    bucket[C[i]]++;
  }
  SC.resize(n + 2, 0);
  for (int i = n; i >= 0; i--) {
    SC[i] = SC[i + 1] + bucket[i];
  }
  dp.clear();
  dp.resize(n + 1, vector<vector<mint>>(n + 1, vector<mint>(n + 1, 0)));
  dp[0][0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {    // j = [0, i]
      for (int k = 0; k <= i; k++) {  // k = [0, i]
        assert(S[i + 1] == '1');
        if (dp[i][j][k] == 0) continue;
        // 下个人想要不挂，忍耐度 C[i] 需要大于 j, 即在忍耐度为 [j+1, n] 之间选择1个人
        // 目前已经选择了 k 个人，可选择的只有 Ranges(j+1,n) - k
        const ll allGreater = Ranges(j + 1, n);
        if (allGreater >= k) {
          dp[i + 1][j][k + 1] += dp[i][j][k] * (allGreater - k);
        }

        // 下个人想要挂掉，忍耐度 C[i] 需要小于等于 j,  即在忍耐度为 [0, j] 之间选择1个人。
        // 目前已经选择了 i-k 个人，可选择的只有 Ranges(0,j) - (i-k)
        // 还需要枚举 k 个忍耐度大于 j 的人中，有多少个忍耐度等于 j+1
        const ll allLessEqual = Ranges(0, j);
        const ll chosenLessEqual = i - k;
        if (allLessEqual >= chosenLessEqual) {
          for (int t = 0; t <= min(k, bucket[j + 1]); t++) {
            dp[i + 1][j + 1][k - t] += dp[i][j][k] * (allLessEqual - chosenLessEqual);
          }
        }
      }
    }
  }

  mint ans = 0;
  for (int j = 0; j <= n - m; j++) {
    for (int k = 0; k <= n; k++) {
      ans += dp[n][j][k];
    }
  }
  return ans.x;
}

/*
3 2
111
1 0 2

*/

};  // namespace DP_ALL_S1

void Solver() {  //
  scanf("%d%d", &n, &m);
  scanf("%s", S + 1);
  C.resize(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &C[i]);
  }
  // 特殊性质 A: 对于所有 i，均有 s[i]=1。
  for (int i = 0; i <= n; i++) {
    printf("m=%d, ans = %lld\n", i, DP_ALL_S1::Solver(i));
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
  }
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    int fileIndex = i;
    string fileAns = string(TASK) + to_string(fileIndex) + ".ans";
    string fileOut = string(TASK) + to_string(fileIndex) + ".out";
    string cmd = string("diff -w " + fileAns + " " + fileOut);
    if (system(cmd.c_str())) {
      printf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
    } else {
      printf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
#endif
  return 0;
}
