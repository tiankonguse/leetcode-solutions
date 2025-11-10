/*
ID: tiankonguse
TASK: poetize
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "poetize"
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
int debug_log = 1;
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

/*
AC 自动机模板

支持多个 AC 自动机同时工作。
每个 AC 自动机有自己的 root 节点，通过 root 节点操作对应的 AC 自动机。

int root = AC::NextNode();  // 创建一个 AC 自动机，返回其 root 节点编号
AC::insert(root, pattern);  // 向对应 AC 自动机插入模式串
AC::build(root);            // 构建对应 AC 自动机
ll res = AC::query(root, text);  // 在对应 AC 自动机中查询 text 中出现的模式串总数

*/

namespace AC {
constexpr int kNodeSize = 1e6 + 6;
const int kKind = 10;
struct Node {
  int son[kKind];  // 子结点
  int cnt;         // 尾为该结点的串的个数
  int fail;        // fail 指针

  void init() {  // 结点初始化
    memset(son, 0, sizeof(son));
    cnt = fail = 0;
  }
} tr[kNodeSize];

int tot = 0;  // 结点总数

int NextNode() {
  int id = tot++;
  tr[id].init();
  return id;
}
int Hash(char c) { return c - '0'; }

void insert(const int root, const char* s) {
  int u = root;
  //   int pre = -1;
  for (int i = 0; s[i]; i++) {
    int& son = tr[u].son[Hash(s[i])];  // 下一个子结点的引用
    if (!son) son = NextNode();        // 如果没有则插入新结点，并初始化
                                       //     pre = u;
    u = son;                           // 从下一个结点继续
  }
  tr[u].cnt++;
  //   MyPrintf("Insert pattern: %s, ends at node %d cnt=%d pre=%d\n", s, u, tr[u].cnt, pre);
}

void build(const int root) {
  queue<int> q;
  // 为每个独立的 root 设置自己的 fail/缺失转移指向自己
  tr[root].fail = root;
  // 根节点的直接子结点：设置其 fail 为 root，并入队；根节点缺失转移指向 root 自身
  for (int i = 0; i < kKind; i++) {
    if (tr[root].son[i]) {
      tr[tr[root].son[i]].fail = root;
      q.push(tr[root].son[i]);
    } else {
      tr[root].son[i] = root;  // 根节点缺失转移指向 root 自身
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < kKind; i++) {
      if (tr[u].son[i]) {                               // 存在对应子结点
        tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];  // 只用跳一次 fail 指针
        q.push(tr[u].son[i]);                           // 并加入队列
      } else {
        tr[u].son[i] = tr[tr[u].fail].son[i];  // 将不存在的字典树的状态链接到了失配指针的对应状态
      }
    }
  }
}

ll query(const int root, const char* t) {
  int u = root;
  ll res = 0;
  for (int i = 0; t[i]; i++) {
    u = tr[u].son[Hash(t[i])];  // 转移
    // 沿 fail 链累加，终止条件为回到当前 automaton 的 root
    for (int j = u; j != root; j = tr[j].fail) {
      res += tr[j].cnt;
    }
    // 如果 root 本身也为模式结尾（极少见），也需要计入
    if (tr[root].cnt) res += tr[root].cnt;
  }
  return res;
}

ll query(const int root, const int node, const char c) {
  int u = node;
  u = tr[u].son[Hash(c)];  // 转移
  if (u == root) return -1;
  if (tr[u].cnt) return 0;
  return u;
}

struct AcAutomaton {
  int root;
  AcAutomaton() { root = NextNode(); }
  void Insert(const char* s) { insert(root, s); }
  void Build() { build(root); }
  ll Query(const char* t) { return query(root, t); }
  ll Query(int node, const char c) { return query(root, node, c); }
};

};  // namespace AC

AC::AcAutomaton trie;
int N, X, Y, Z;
string buf;
const int MOD = 998244353;

enum { NUM_X = 0, NUM_Y = 1, NUM_Z = 2 };
void AddOneAns() {  //
  trie.Insert(buf.c_str());
  //   MyPrintf("Add pattern: %s\n", buf.c_str());
}
void DfsInit(int num, int sum) {
  if (num == NUM_X && sum >= X) {
    if (sum == X) {
      DfsInit(NUM_Y, 0);
    }
    return;
  }
  if (num == NUM_Y && sum >= Y) {
    if (sum == Y) {
      DfsInit(NUM_Z, 0);
    }
    return;
  }
  if (num == NUM_Z && sum >= Z) {
    if (sum == Z) {
      AddOneAns();
    }
    return;
  }
  for (int i = 1; i <= 7; i++) {
    buf.push_back('0' + i);
    DfsInit(num, sum + i);
    buf.pop_back();
  }
}
ll pow10[50];

void Init() {
  pow10[0] = 1;
  for (int i = 1; i < 50; i++) {
    pow10[i] = (pow10[i - 1] * 10) % MOD;
  }
}

void Solver() {  //
  scanf("%d%d%d%d", &N, &X, &Y, &Z);
  Init();
  DfsInit(NUM_X, 0);
  trie.Build();
  unordered_map<ll, ll> q1, q2;
  q1[trie.root] = 1;
  ll ans = 0;
  for (int i = 0; i < N; i++) {
    q2.clear();
    for (auto [u, cnt] : q1) {
      //   MyPrintf("At pos %d, node %lld, cnt %lld\n", i, u, cnt);
      for (int j = 1; j <= 7; j++) {
        const char c = '0' + j;
        ll v = trie.Query(u, c);
        // if (u == 66) {
        //   MyPrintf("  Try char %c, from node %lld to node %lld\n", c, u, v);
        // }
        if (v == -1) {  // 前缀全部无效
          q2[trie.root] += cnt;
          q2[trie.root] %= MOD;
        } else if (v == 0) {  // 匹配成功
          //   MyPrintf("  Match at char %c, from node %lld to node %lld, cnt=%lld left=%d pow10=%lld\n", c, u, v, cnt,
          //            N - 1 - i, pow10[N - 1 - i]);
          ans += (cnt * pow10[N - 1 - i]) % MOD;
          ans %= MOD;
        } else {
          q2[v] += cnt;
          q2[v] %= MOD;
        }
      }
      for (int j = 8; j <= 10; j++) {
        q2[trie.root] += cnt;
        q2[trie.root] %= MOD;
      }
    }
    q2.swap(q1);
  }
  printf("%lld\n", ans);
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
