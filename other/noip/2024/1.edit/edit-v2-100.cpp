/*
ID: tiankonguse
TASK: edit
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "edit"
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
#define LOCAL_IO 1
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

int n;
char s[2][max5];
char t[2][max5];

enum NodeType {
  TYPE_CONST = 0,
  TYPE_SWAP = 1,
};
struct Node {
  int type;
  int v[2] = {0, 0};
  Node(int type = TYPE_CONST) : type(type) {
    v[0] = 0;
    v[1] = 0;
  }
  Node(int type, int val) : type(type) {
    v[val] = 1;
    v[1 - val] = 0;
  }
  void Add(int x) { v[x]++; }
  bool TryPop(int x) {
    if (v[x]) {
      v[x]--;
      return true;
    } else {
      v[1 - x]--;
      return false;
    }
  }
  int Size() const { return v[0] + v[1]; }
};
vector<Node> nodes[2];
void Init(vector<Node>& nodes, char* s, char* t) {
  nodes.clear();
  nodes.push_back(Node(NodeType::TYPE_CONST, 0));  // 哨兵
  for (int i = 0; i < n; i++) {
    const int type = t[i] - '0';
    const int v = s[i] - '0';
    if (type == NodeType::TYPE_CONST) {
      nodes.push_back(Node(NodeType::TYPE_CONST, v));
    } else {
      if (nodes.back().type == NodeType::TYPE_SWAP) {
        nodes.back().Add(v);
      } else {
        nodes.push_back(Node(NodeType::TYPE_SWAP, v));
      }
    }
  }
  MyPrintf("nodes.size=%lu\n", nodes.size());
  for (auto& node : nodes) {
    MyPrintf("type=%d, v[0]=%d, v[1]=%d\n", node.type, node.v[0], node.v[1]);
  }
}
void SolverCase() {
  scanf("%d", &n);
  scanf("%s%s", s[0], s[1]);
  scanf("%s%s", t[0], t[1]);
  Init(nodes[0], s[0], t[0]);
  Init(nodes[1], s[1], t[1]);
  int ans = 0;
  while (n--) {
    int p0 = 0, p1 = 1;
    if (nodes[p0].back().Size() > nodes[p1].back().Size()) {
      swap(p0, p1);
    }
    // 大的匹配小的
    int v = 0;
    if (!nodes[p0].back().TryPop(v)) {
      v = 1 - v;
    }
    if (nodes[p1].back().TryPop(v)) {
      ans++;
    }
    for (int i = 0; i < 2; i++) {
      if (nodes[i].back().Size() == 0) {
        nodes[i].pop_back();
      }
    }
  }
  printf("%d\n", ans);
}

void Solver() {  //
  int T;
  scanf("%d", &T);
  while (T--) {
    SolverCase();
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

/*
6
s1: 011101
t1: 111010
s2: 111010
t2: 101101
*/