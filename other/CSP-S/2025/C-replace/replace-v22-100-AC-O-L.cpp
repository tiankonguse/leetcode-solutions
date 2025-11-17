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
#define TASKEX "-v22-100-AC-O-L"

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

namespace AC {
constexpr int kNodeSize = 1e7 + 6;
const int kKind = 27;
struct Node {
  int son[kKind];  // 子结点
  int cnt;         // 尾为该结点的串的个数
  int fail;        // fail 指针
  int preFlag;     // 前缀和是否计算
  int preCnt;      // 前缀和

  void init() {  // 结点初始化
    memset(son, 0, sizeof(son));
    cnt = fail = preFlag = preCnt = 0;
  }
} tr[kNodeSize];

int tot = 0;  // 结点总数

int NextNode() {
  int id = tot++;
  tr[id].init();
  return id;
}
int Hash(char c) {
  if (c == ' ') return kKind - 1;  // 特殊字符
  return c - 'a';
}

void insert(const int root, char s[]) {
  int u = root;
  for (int i = 0; s[i]; i++) {
    int& son = tr[u].son[Hash(s[i])];  // 下一个子结点的引用
    if (!son) son = NextNode();        // 如果没有则插入新结点，并初始化
    u = son;                           // 从下一个结点继续
  }
  tr[u].cnt++;
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
int UpPre(int p) {
  if (tr[p].preFlag) return tr[p].preCnt;
  tr[p].preFlag = 1;
  return tr[p].preCnt = tr[p].cnt + UpPre(tr[p].fail);
}
ll query(const int root, char t[]) {
  int u = root;
  ll res = 0;
  for (int i = 0; t[i]; i++) {
    u = tr[u].son[Hash(t[i])];  // 转移
    // 沿 fail 链累加，终止条件为回到当前 automaton 的 root
    res += UpPre(u);
    // for (int j = u; j != root; j = tr[j].fail) {
    //   res += tr[j].cnt;
    // }
    // 如果 root 本身也为模式结尾（极少见），也需要计入
    // if (tr[root].cnt) res += tr[root].cnt;
  }
  return res;
}
}  // namespace AC

namespace HASH {
const ll mod1e7 = 1000000007, mod1e9 = 1000000009;
const ll BASE = 29;  // [a-z] -> [1-26], ' ' -> 27
inline ll Hash(char c) {
  if (c == ' ') return 27;
  return c - 'a' + 1;
}
inline ll Hash(ll pre, char c) { return (pre * BASE + Hash(c)) % mod1e7; }
ll Hash(ll pre, const char* str, int l, int r) {  // [l, r)
  for (int i = l; i < r; i++) {
    pre = Hash(pre, str[i]);
  }
  return pre;
}
inline ll Hash(const char* str, int l, int r) { return Hash(0, str, l, r); }
};  // namespace HASH

const int MAXN = 6e6 + 6;
int n, q;
char s1[MAXN], s2[MAXN], s3[MAXN];
unordered_map<ll, int> ACIndex;  // AC 自动机的根节点

ll MergeS1S2(int len) {
  int leftLen = 0, rightLen = len - 1;  // [leftLen, rightLen] 是不同的区间
  int mergeLen = 0;
  while (leftLen < len && s1[leftLen] == s2[leftLen]) {
    s3[mergeLen++] = s1[leftLen];
    leftLen++;
  }
  s3[mergeLen++] = ' ';
  while (rightLen >= 0 && s1[rightLen] == s2[rightLen]) {
    s3[mergeLen++] = s1[rightLen];
    rightLen--;
  }
  // 翻转 s3 的后半部分 [rightLen+1, mergeLen-1]
  std::reverse(s3 + leftLen + 1, s3 + mergeLen);
  s3[mergeLen] = '\0';

  ll h = HASH::Hash(s1, leftLen, rightLen + 1);
  h = HASH::Hash(h, ' ');
  h = HASH::Hash(h, s2, leftLen, rightLen + 1);
  return h;
}

void Solver() {  //
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) {
    scanf("%s%s", s1, s2);
    int len = strlen(s1);
    ll h = MergeS1S2(len);
    if (ACIndex.count(h) == 0) {
      ACIndex[h] = AC::NextNode();  // 创建一个 AC 自动机
    }
    // 插入 AC 自动机
    AC::insert(ACIndex[h], s3);
  }

  // 构建 AC 自动机
  for (auto& [_, root] : ACIndex) {
    AC::build(root);
  }

  // q 个询问
  while (q--) {
    scanf("%s%s", s1, s2);
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 != len2) {
      printf("0\n");  // 长度不同，直接输出 0
      continue;
    }
    ll h = MergeS1S2(len1);
    if (ACIndex.count(h) == 0) {
      printf("0\n");  // 不存在该模式串，直接输出 0
      continue;
    }
    int root = ACIndex[h];
    ll res = AC::query(root, s3);
    printf("%lld\n", res);
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
