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
char s1[max5], s2[max5];
char t1[max5], t2[max5];
enum NodeType {
  TYPE_CONST = 0,
  TYPE_SWAP = 1,
};
struct Node {
  int type;
  int val = 0;
  int v[2] = {0, 0};
  Node(int type = 0, int val = 0) : type(type), val(val) {}
  void Add(int x) {
    v[x]++;
    val++;
  }
  bool Has(int x) const { return v[x] > 0; }
  bool TryPop(int x) {
    val--;
    if (Has(x)) {
      v[x]--;
      return true;
    } else {
      v[1 - x]--;
      return false;
    }
  }
  bool Empty() const { return val == 0; }
  int Size() const { return val; }
};
vector<Node> nodes1, nodes2;
void Init(vector<Node>& nodes, char* s, char* t) {
  nodes.clear();
  nodes.push_back(Node(NodeType::TYPE_CONST, 0));  // 哨兵
  for (int i = 0; i < n; i++) {
    const int type = t[i] - '0';
    const int v = s[i] - '0';
    if (type == NodeType::TYPE_CONST) {
      nodes.push_back(Node(NodeType::TYPE_CONST, s[i] - '0'));
    } else {
      if (nodes.back().type == NodeType::TYPE_SWAP) {
        nodes.back().Add(v);
      } else {
        Node node(NodeType::TYPE_SWAP, 0);
        node.Add(v);
        nodes.push_back(node);
      }
    }
  }
}
void SolverCase() {
  scanf("%d", &n);
  scanf("%s%s", s1, s2);
  scanf("%s%s", t1, t2);
  Init(nodes1, s1, t1);
  Init(nodes2, s2, t2);
  int ans = 0;
  auto MergeConstSwap = [&ans](vector<Node>& nodes1, vector<Node>& nodes2) {
    assert(nodes1.back().type == NodeType::TYPE_CONST);
    assert(nodes2.back().type == NodeType::TYPE_SWAP);
    const int val = nodes1.back().val;
    nodes1.pop_back();
    if (nodes2.back().TryPop(val)) {
      ans++;
    }
    if (nodes2.back().Empty()) {
      nodes2.pop_back();
    }
  };
  auto MergeSwapSwap = [&ans](vector<Node>& nodes1, vector<Node>& nodes2) {
    assert(nodes1.back().type == NodeType::TYPE_SWAP);
    assert(nodes2.back().type == NodeType::TYPE_SWAP);
    assert(nodes1.back().Size() <= nodes2.back().Size());
    if (nodes1.back().Has(0)) {
      nodes1.back().TryPop(0);
      if (nodes2.back().TryPop(0)) {
        ans++;
      }
    } else {
      nodes1.back().TryPop(1);
      if (nodes2.back().TryPop(1)) {
        ans++;
      }
    }
    if (nodes1.back().Empty()) {
      nodes1.pop_back();
    }
    if (nodes2.back().Empty()) {
      nodes2.pop_back();
    }
  };
  while (n--) {
    if (nodes1.back().type == NodeType::TYPE_CONST && nodes2.back().type == NodeType::TYPE_CONST) {
      if (nodes1.back().val == nodes2.back().val) {
        ans++;
      }
      nodes1.pop_back();
      nodes2.pop_back();
    } else if (nodes1.back().type == NodeType::TYPE_CONST) {  // nodes2 swap
      MergeConstSwap(nodes1, nodes2);
    } else if (nodes2.back().type == NodeType::TYPE_CONST) {  // nodes1 swap
      MergeConstSwap(nodes2, nodes1);
    } else {  // swap swap
      if (nodes1.back().Size() > nodes2.back().Size()) {
        MergeSwapSwap(nodes2, nodes1);
      } else {
        MergeSwapSwap(nodes1, nodes2);
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