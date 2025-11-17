/*
ID: tiankonguse
TASK: replace
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
注： 标准的 AC 自动机模板，支持多个 AC 自动机同时工作
*/
#define TASK "replace"
#define TASKEX "-v20-100-AC-O-L"

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
const int N = 200010, L = 5000010, C = 27;
const char _ = 'z' + 1;
int n, m, tree[L][C], cnt, ed[L], fail[L], st[L], preEd[L], preFlag[L], dfsFlag[L];
string s, s1, s2;

void add(string& s) {
  int p = 0;
  for (char c : s) {
    int x = c - 'a';
    if (!tree[p][x]) tree[p][x] = ++cnt;
    p = tree[p][x];
  }
  ++ed[p];
}

void build() {
  queue<int> q;
  for (int j = 0; j < C; ++j) {
    int p = tree[0][j];
    if (p) {
      q.emplace(p);
    }
  }
  while (q.size()) {
    int p = q.front();
    q.pop();
    for (int j = 0; j < C; ++j) {
      if (!tree[p][j]) {
        tree[p][j] = tree[fail[p]][j];
      } else {
        fail[tree[p][j]] = tree[fail[p]][j];
        q.emplace(tree[p][j]);
      }
    }
  }
}

int UpPre(int p) {
  if (preFlag[p]) return preEd[p];
  preFlag[p] = 1;
  return preEd[p] = ed[p] + UpPre(fail[p]);
}

void DfsPre(const int root) {
  if (dfsFlag[root]) return;
  dfsFlag[root] = 1;
  for (int j = 0; j < C; ++j) {
    int p = tree[root][j];
    preFlag[p] = 1;
    preEd[p] = ed[p] + UpPre(fail[p]);
    DfsPre(p);
  }
}

int ask(string& s, int id) {
  int res = 0, p = 0;
  for (char c : s) {
    p = tree[p][c - 'a'];
    res += preEd[p];
    // for (int j = p; j && st[j] != id; j = fail[j]) {
    //   res += ed[j];
    //   st[j] = id;
    // }
  }
  return res;
}

void Solver() {  //
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> s1 >> s2;
    int n1 = s1.size(), j = 0, k = n1;
    for (; j < n1 && s1[j] == s2[j]; ++j);
    if (j == n1) continue;
    for (; ~k && s1[k] == s2[k]; --k);
    s = s1.substr(0, j) + _ + s1.substr(j, k - j + 1) + s2.substr(j, k - j + 1) + _ + s1.substr(k + 1, n1 - k);
    // cout << s << '\n';
    add(s);
  }
  build();
  DfsPre(0);
  for (int i = 1; i <= m; ++i) {
    cin >> s1 >> s2;
    int n1 = s1.size(), n2 = s2.size();
    if (n1 != n2) {
      cout << "0\n";
      continue;
    }
    int j = 0, k = n1;
    for (; j < n1 && s1[j] == s2[j]; ++j);
    for (; ~k && s1[k] == s2[k]; --k);
    s = s1.substr(0, j) + _ + s1.substr(j, k - j + 1) + s2.substr(j, k - j + 1) + _ + s1.substr(k + 1, n1 - k);
    // cout << s << '\n';
    cout << ask(s, i) << '\n';
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
