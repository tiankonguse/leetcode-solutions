/*
ID: tiankonguse
TASK: replace
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
注： 不带预处理的 KMP
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

const int MAXN = 6e6 + 6;
int n, q;
char s1[MAXN], s2[MAXN], s3[MAXN];

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

vector<string> patterns;

unordered_map<ll, vector<pair<string, vector<int>>>> mp;

namespace KMP {
// 前缀函数 next[i]： 前缀 [0,j] 的最长公共前后缀的长度
// 即第 j 位匹配失败时，说明 pat[0,j-1] 与前缀是匹配的，此时 j 应该回退到 next[j-1]+1 重新开始匹配
// 扩展: 计算 Next 是一个在线算法，可以按顺序计算 Next 数组，故可以计算树上的 Next
//
// 应用:
// - 在字符串中查找子串：Knuth–Morris–Pratt 算法
// - 字符串的周期: n - (next[n-1]+1)
// - 统计每个前缀的出现次数
// - 一个字符串中本质不同子串的数目
// - 字符串压缩
// - 根据前缀函数构建一个自动机
// https://oi-wiki.org/string/kmp/
//

vector<int> next;
void getNext(const char* pat, vector<int>& next) {
  next[0] = -1;
  for (int i = 1; pat[i]; ++i) {
    next[i] = -1;
    int k = next[i - 1];
    while (k >= 0 && pat[k + 1] != pat[i]) {
      k = next[k];
    }
    if (pat[k + 1] == pat[i]) {
      next[i] = k + 1;
    }
  }
}
int kmp(const char* str, const char* pat, int patLen) {
  next.resize(patLen + 1, -1);
  next[patLen] = -1;
  getNext(pat, next);
  int i = 0, j = 0;
  while (str[i] && pat[j]) {
    if (pat[j] == str[i]) {
      ++i;
      if (!pat[++j]) {
        return i - j;
      }
    } else if (j == 0) {
      ++i;
    } else {
      j = next[j - 1] + 1;
    }
  }
  return -1;
}
int kmp(const char* str, const char* pat, int patLen, const vector<int>& next) {
  int i = 0, j = 0;
  while (str[i] && pat[j]) {
    if (pat[j] == str[i]) {
      ++i;
      if (!pat[++j]) {
        return i - j;
      }
    } else if (j == 0) {
      ++i;
    } else {
      j = next[j - 1] + 1;
    }
  }
  return -1;
}
}  // namespace KMP

void Solver() {  //
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) {
    scanf("%s%s", s1, s2);
    int len = strlen(s1);
    ll h = MergeS1S2(len);
    mp[h].resize(mp[h].size() + 1);
    auto& [s, nextVec] = mp[h].back();
    s = string(s3);
    nextVec.resize(s.length() + 1, -1);
    KMP::getNext(s.c_str(), nextVec);
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
    if (mp.count(h) == 0) {
      printf("0\n");  // 不存在该模式串，直接输出 0
      continue;
    }
    ll res = 0;
    for (const auto& [pat, nextVec] : mp[h]) {
      if (KMP::kmp(s3, pat.c_str(), pat.length(), nextVec) != -1) {
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
