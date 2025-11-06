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

namespace TRIE {

const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 6000010, max7 = 20000010;
struct Node {
  int next[26];
};
Node nodes[max6];
int queryFlag[max6];
int index = 0;

void Init() {
  index = 0;
  memset(queryFlag, 0, sizeof(queryFlag));
}

class Trie {
  int root_index = 0;
  void Clear(int root) {
    Node& node = nodes[root];
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

  void Init() { root_index = Add(); }

  /** Inserts a word into the trie. */
  int Insert(const char* word) {
    int root = root_index;
    while (*word) {
      int v = *word - 'a';
      if (nodes[root].next[v] == -1) {
        nodes[root].next[v] = Add();
      }
      root = nodes[root].next[v];
      word++;
    }
    return root;
  }

  /** Returns if the word is in the trie. */
  void Search(const char* word, int queryIndex) {
    int root = root_index;
    queryFlag[root] = queryIndex;
    while (*word) {
      int v = *word - 'a';
      int p = nodes[root].next[v];
      if (p == -1) return;
      root = p;
      queryFlag[root] = queryIndex;
      word++;
    }
  }
};
};  // namespace TRIE

const int MAXN = 6e6 + 6;
int n, q;
char s1[MAXN], s2[MAXN];
char S1[MAXN], S2[MAXN];
int S1Len = 0, S2Len = 0;

struct GroupInfo {
  TRIE::Trie trie1;
  TRIE::Trie trie2;
  vector<pair<int, int>> patterns;  // 存储该组的所有模式串对应的终止结点
};

unordered_map<ll, GroupInfo> ACIndex;

ll MergeS1S2(int len) {
  int leftLen = 0, rightLen = len - 1;  // [leftLen, rightLen] 是不同的区间
  S1Len = 0, S2Len = 0;
  while (leftLen < len && s1[leftLen] == s2[leftLen]) {
    S1[S1Len++] = s1[leftLen++];
  }
  S1[S1Len] = '\0';
  while (rightLen >= 0 && s1[rightLen] == s2[rightLen]) {
    S2[S2Len++] = s1[rightLen--];
  }
  S2[S2Len] = '\0';

  ll h = HASH::Hash(s1, leftLen, rightLen + 1);
  h = HASH::Hash(h, ' ');
  h = HASH::Hash(h, s2, leftLen, rightLen + 1);
  std::reverse(S1, S1 + S1Len);
  std::reverse(S2, S2 + S2Len);
  return h;
}

void Solver() {  //
  TRIE::Init();
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) {
    scanf("%s%s", s1, s2);
    int len = strlen(s1);
    ll h = MergeS1S2(len);
    if (ACIndex.count(h) == 0) {
      auto& groupInfo = ACIndex[h];
      groupInfo.trie1.Init();
      groupInfo.trie2.Init();
    }
    // 插入字典表 Trie
    auto& groupInfo = ACIndex[h];
    int node1 = groupInfo.trie1.Insert(S1);
    int node2 = groupInfo.trie2.Insert(S2);
    groupInfo.patterns.push_back({node1, node2});
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
    auto& groupInfo = ACIndex[h];
    groupInfo.trie1.Search(S1, q + 1);
    groupInfo.trie2.Search(S2, q + 1);
    ll res = 0;
    for (auto [node1, node2] : groupInfo.patterns) {
      if (TRIE::queryFlag[node1] == q + 1 && TRIE::queryFlag[node2] == q + 1) {
        res++;
      }
    }
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
