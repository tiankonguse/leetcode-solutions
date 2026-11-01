/*
ID: tiankonguse
TASK: Trie
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P8306?contestId=367097
PATH: P8306 【模板】字典树 / Trie
submission:
*/
#define TASK "Trie"
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
// const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

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

// A-Za-z0-9 共 62 个字符，大于 62 的最小质数为 67。
vector<ll> charIndex;
void Init() {
  charIndex.resize(256);
  int index = 0;
  for (char c = 'a'; c <= 'z'; c++) {
    charIndex[c] = index++;
  }
  for (char c = 'A'; c <= 'Z'; c++) {
    charIndex[c] = index++;
  }
  for (char c = '0'; c <= '9'; c++) {
    charIndex[c] = index++;
  }
}
int Index(char c) {
  return charIndex[c];  //
}

const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 3000010;
struct Node {
  int endFlag = 0;  // 是否是结束标示符
  int num = 0;
  int next[67];
};
Node nodes[max6];
class Trie {
  int index = 0;

  void Clear(int root) {
    Node& node = nodes[root];
    node.endFlag = false;
    node.num = 0;
    memset(node.next, -1, sizeof(node.next));
  }

  int Add() {
    int ret = index;
    Clear(ret);
    index++;
    return ret;
  }

 public:
  /** Initialize your data structure here. */
  Trie() { Init(); }

  void Init() {
    index = 0;
    Add();
  }

  /** Inserts a word into the trie. */
  void Insert(const char* p) {
    int root = 0;
    while (*p) {
      int v = Index(*p);
      p++;
      if (nodes[root].next[v] == -1) {
        nodes[root].next[v] = Add();
      }
      nodes[root].num++;
      MyPrintf("v = %d, root = %d, num = %d, next = %d\n", v, root, nodes[root].num, nodes[root].next[v]);
      root = nodes[root].next[v];
    }
    nodes[root].num++;
    nodes[root].endFlag = 1;
    MyPrintf("root = %d, num = %d, endFlag = %d\n", root, nodes[root].num, nodes[root].endFlag);
  }

  /** Returns if the word is in the trie. */
  int Count(const char* p, int root = 0) {
    while (*p) {
      int v = Index(*p);
      p++;
      MyPrintf("Search v = %d, root = %d, next = %d\n", v, root, nodes[root].next[v]);
      if (nodes[root].next[v] == -1) return 0;
      root = nodes[root].next[v];
    }
    MyPrintf("Search root = %d, num = %d\n", root, nodes[root].num);
    return nodes[root].num;
  }
};

Trie trie;

int t, n, q;
char str[max6];
void Solver() {  //
  Init();
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &q);
    trie.Init();
    for (int i = 0; i < n; i++) {
      scanf("%s", str);
      trie.Insert(str);
    }
    for (int i = 0; i < q; i++) {
      scanf("%s", str);
      printf("%d\n", trie.Count(str));
    }
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
