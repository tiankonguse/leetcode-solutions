/*
ID: tiankonguse
TASK: replace
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
注：DA 算法， n log(n)
*/
#define TASK "replace"
#define TASKEX "-sa-v11-70"

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
#ifdef LOCAL_IO
#ifdef USACO_LOCAL_JUDGE
#define MAX_TIME 2000
#define USACO_TASK_FILE 20

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

namespace DA {
const int maxn = 6e6 + 10;
int wx[maxn], wy[maxn], *x, *y, wss[maxn], wv[maxn];

bool cmp(int* r, int n, int a, int b, int l) { return a + l < n && b + l < n && r[a] == r[b] && r[a + l] == r[b + l]; }
void da(char str[], int sa[], int rank[], int height[], int n, int m) {
  char* s = str;
  int *x = wx, *y = wy, *t, p;
  int i, j;
  for (i = 0; i < m; i++) wss[i] = 0;
  for (i = 0; i < n; i++) wss[x[i] = s[i]]++;
  for (i = 1; i < m; i++) wss[i] += wss[i - 1];
  for (i = n - 1; i >= 0; i--) sa[--wss[x[i]]] = i;
  for (j = 1, p = 1; p < n && j < n; j *= 2, m = p) {
    for (i = n - j, p = 0; i < n; i++) y[p++] = i;
    for (i = 0; i < n; i++)
      if (sa[i] - j >= 0) y[p++] = sa[i] - j;
    for (i = 0; i < n; i++) wv[i] = x[y[i]];
    for (i = 0; i < m; i++) wss[i] = 0;
    for (i = 0; i < n; i++) wss[wv[i]]++;
    for (i = 1; i < m; i++) wss[i] += wss[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--wss[wv[i]]] = y[i];
    for (t = x, x = y, y = t, p = 1, i = 1, x[sa[0]] = 0; i < n; i++)
      x[sa[i]] = cmp(y, n, sa[i - 1], sa[i], j) ? p - 1 : p++;
  }
  for (int i = 0; i < n; i++) rank[sa[i]] = i;
  for (int i = 0, j = 0, k = 0; i < n; height[rank[i++]] = k)
    if (rank[i] > 0)
      for (k ? k-- : 0, j = sa[rank[i] - 1]; i + k < n && j + k < n && str[i + k] == str[j + k]; k++);
}

int sa[maxn];      // 第几名的位置, 对应 sa
int rk[maxn];      // 第几个元素排第几名, 对应 rk
int height[maxn];  // 第几名与上一名的最长前缀, 对应 height

void BuildRA(char* str, int n, int m = 256) {  //  m 为值域
  da(str, sa, rk, height, n, m);
}
};  // namespace DA

const int MAXN = 6e6 + 6;
int n, q;
ll ans[max5];

// S(最小): S3 + '('
// T(大于S): T3 + '?'
// S(大于T): S3 + '}'
const char S3_TOP = '(';
const char T3_MIDDLE = '?';
const char S3_BOTTOM = '}';
const char S3_JOIN = '#';
const char BUF_END = '~';
char baseBuf[MAXN * 2];
int baseBufLen = 0;
char s1[MAXN], s2[MAXN];
pair<ll, string_view> MergeS1S2(int len) {
  int leftLen = 0, rightLen = len - 1;  // [leftLen, rightLen] 是不同的区间
  int mergeLen = 0;
  char* s3 = baseBuf + baseBufLen;
  while (leftLen < len && s1[leftLen] == s2[leftLen]) {
    s3[mergeLen++] = s1[leftLen];
    leftLen++;
  }
  s3[mergeLen++] = S3_JOIN;
  while (rightLen >= 0 && s1[rightLen] == s2[rightLen]) {
    s3[mergeLen++] = s1[rightLen];
    rightLen--;
  }
  // 翻转 s3 的后半部分 [rightLen+1, mergeLen-1]
  std::reverse(s3 + leftLen + 1, s3 + mergeLen);
  s3[mergeLen] = '\0';
  baseBufLen += (mergeLen + 1);

  ll h = HASH::Hash(s1, leftLen, rightLen + 1);
  h = HASH::Hash(h, ' ');
  h = HASH::Hash(h, s2, leftLen, rightLen + 1);
  return {h, string_view(s3, mergeLen)};
}
struct SInfo {
  string_view s;
  int offset1, offset2;
};
struct TInfo {
  string_view s;
  int idx;
  int offsetLeft, offsetRight;
};
struct STInfo {
  vector<SInfo> patterns;
  vector<TInfo> queries;
};

unordered_map<ll, STInfo> mp;

int differenceArray[MAXN * 2];
int queryOffset[max5];
char buf[MAXN * 2];
int bufLen = 0;
void BuildRaBuf(STInfo& info) {
  auto& patterns = info.patterns;
  auto& queries = info.queries;
  // S+'('
  // S + '}'
  // T + '?'
  bufLen = 0;
  for (auto& pattern : patterns) {
    pattern.offset1 = bufLen;
    for (auto c : pattern.s) {
      buf[bufLen++] = c;
    }
    buf[bufLen++] = S3_TOP;

    pattern.offset2 = bufLen;
    for (auto c : pattern.s) {
      buf[bufLen++] = c;
    }
    buf[bufLen++] = S3_BOTTOM;
  }
  for (auto& query : queries) {
    query.offsetLeft = bufLen;
    for (auto c : query.s) {
      buf[bufLen++] = c;
    }
    buf[bufLen++] = T3_MIDDLE;
    query.offsetRight = bufLen;
  }
  buf[bufLen++] = BUF_END;
  buf[bufLen] = '\0';
}

int maxSALen = 0;
void SolverGroup(STInfo& info) {
  auto& patterns = info.patterns;
  auto& queries = info.queries;
  const int qn = queries.size();
  BuildRaBuf(info);
  MyPrintf("buf=%s\n", buf);
  const int totalLen = bufLen;
  maxSALen = max(maxSALen, totalLen);

  // memset(differenceArray, 0, sizeof(differenceArray[0]) * (totalLen + 2));
  for (int i = 0; i < qn; i++) {
    auto& query = queries[i];
    MyPrintf("i=%d t=%s offsetRange[%d, %d) \n", query.idx, query.s.data(), query.offsetLeft, query.offsetRight);
    queryOffset[i] = query.offsetLeft;
  }

  DA::BuildRA(buf, totalLen);
  for (auto& pattern : patterns) {
    int r1 = DA::rk[pattern.offset1];
    int r2 = DA::rk[pattern.offset2];
    // r1 一定小于 r2
    assert(r1 < r2);
    MyPrintf("s=%s offset1=%d offset2=%d r1=%d r2=%d\n", pattern.s.data(), pattern.offset1, pattern.offset2, r1, r2);
    r1++;
    r2--;
    if (r1 <= r2) {
      differenceArray[r1]++;
      differenceArray[r2 + 1]--;
    }
  }
  auto FindIdx = [&](int offset) {  //
    int i = upper_bound(queryOffset, queryOffset + qn, offset) - queryOffset;
    if (i == 0) return -1;
    i--;
    auto& query = queries[i];
    if (offset >= query.offsetLeft && offset < query.offsetRight) {
      return query.idx;
    }
    return -1;
  };
  int preSum = 0;
  for (int rank = 0; rank <= totalLen; rank++) {
    preSum += differenceArray[rank];
    differenceArray[rank] = 0;
    if (preSum == 0) continue;  // 剪枝
    int offset = DA::sa[rank];
    int queryIdx = FindIdx(offset);
    if (preSum != 0) {
      MyPrintf("rank=%d sum=%d  offset=%d idx=%d\n", rank, preSum, offset, queryIdx);
    }
    if (queryIdx == -1) continue;  // 无效查询
    ans[queryIdx] += preSum;
  }
}

void PreInit() {  // 不应该计算耗时
  mp.clear();
  baseBufLen = 0;
}

void Solver() {  //
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) {
    scanf("%s%s", s1, s2);
    int len = strlen(s1);
    auto [h, s3] = MergeS1S2(len);
    mp[h].patterns.resize(mp[h].patterns.size() + 1);
    auto& patternInfo = mp[h].patterns.back();
    patternInfo.s = s3;
    MyPrintf("i=%d h=%lld s=%s\n", i, h, s3.data());
  }

  // q 个询问
  for (int i = 0; i < q; i++) {
    scanf("%s%s", s1, s2);
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 != len2) {
      continue;  // 长度不同，直接输出 0
    }
    auto [h, s3] = MergeS1S2(len1);
    if (mp.count(h) == 0) {
      continue;  // 不存在该模式串，直接输出 0
    }

    mp[h].queries.resize(mp[h].queries.size() + 1);
    auto& queryInfo = mp[h].queries.back();
    queryInfo.s = s3;
    queryInfo.idx = i;
    MyPrintf("i=%d h=%lld t=%s\n", i, h, s3.data());
  }
  memset(ans, 0, sizeof(ans[0]) * q);

  for (auto& [h, info] : mp) {
    int pn = info.patterns.size();
    int qn = info.queries.size();
    if (pn == 0 || qn == 0) continue;
    MyPrintf("处理 h=%lld patterns=%d queries=%d\n", h, (int)info.patterns.size(), (int)info.queries.size());
    SolverGroup(info);
  }

  for (int i = 0; i < q; i++) {
    printf("%lld\n", ans[i]);
  }
}

#ifdef USACO_LOCAL_JUDGE
double costTime = 0;
#endif
void ExSolver() {
  PreInit();
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
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
  printf("Max SA Length: %d\n", maxSALen);
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

*/