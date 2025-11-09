/*
ID: tiankonguse
TASK: replace
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
注：全局求SA, 40 分
*/
#define TASK "replace"
#define TASKEX "-ra-v16"

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

namespace DC3 {

// 所有下标都是0~n-1，height[0]无意义。
// 所有相关数组都要开三倍
// 0 作为全局最小哨兵，输入字符需映射到 [1..m]
// 原字符串必须以一个最小的且前面没有出现过的字符结尾，这样才能保证结果正确
const int maxn = 6e6 + 10;
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x) * 3 + 1 : ((x) - tb) * 3 + 2)

int wa[maxn * 3], wb[maxn * 3], wv[maxn * 3], ws[maxn * 3];

int c0(const int* r, int a, int b) { return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2]; }
int c12(int k, const int* r, int a, int b) {
  if (k == 2) {
    return r[a] < r[b] || (r[a] == r[b] && c12(1, r, a + 1, b + 1));
  } else {
    return r[a] < r[b] || (r[a] == r[b] && wv[a + 1] < wv[b + 1]);
  }
}
void sort(const int* r, int* a, int* b, int n, int m) {
  int i;
  for (i = 0; i < n; i++) wv[i] = r[a[i]];
  for (i = 0; i <= m; i++) ws[i] = 0;  // m 作为上界
  for (i = 0; i < n; i++) ws[wv[i]]++;
  for (i = 1; i <= m; i++) ws[i] += ws[i - 1];
  for (i = n - 1; i >= 0; i--) b[--ws[wv[i]]] = a[i];
}
void dc3(int* r, int* sa, int n, int m) {
  int i, j;
  int* rn = r + n;    // 使用 r 的后段存放压缩名(需要 r 具备 3n 容量)
  int* san = sa + n;  // sa 的后段作为递归的 sa
  int ta = 0, tb = (n + 1) / 3, tbc = 0, p;

  r[n] = r[n + 1] = 0;  // 哨兵
  for (i = 0; i < n; i++)
    if (i % 3 != 0) wa[tbc++] = i;

  sort(r + 2, wa, wb, tbc, m);
  sort(r + 1, wb, wa, tbc, m);
  sort(r, wa, wb, tbc, m);

  for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++) rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;

  if (p < tbc)
    dc3(rn, san, tbc, p);
  else
    for (i = 0; i < tbc; i++) san[rn[i]] = i;

  for (i = 0; i < tbc; i++)
    if (san[i] < tb) wb[ta++] = san[i] * 3;
  if (n % 3 == 1) wb[ta++] = n - 1;

  sort(r, wb, wa, ta, m);

  for (i = 0; i < tbc; i++) wv[wb[i] = G(san[i])] = i;

  for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++) sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
  for (; i < ta; p++) sa[p] = wa[i++];
  for (; j < tbc; p++) sa[p] = wb[j++];
}

// str 和 sa 也要三倍，但这里 r 在 BuildRA 内部构造，避免修改调用者内存
void da(int r[], int sa[], int rank[], int height[], int n, int m) {
  for (int i = n; i < n * 3; i++) r[i] = 0;  // 清尾保证安全访问
  dc3(r, sa, n + 1, m);                      // 含一个哨兵位

  int i, j, k;
  for (i = 0; i < n; i++) {
    sa[i] = sa[i + 1];  // 去掉哨兵suffix
    rank[sa[i]] = i;
  }
  for (i = 0, j = 0, k = 0; i < n; height[rank[i++]] = k)
    if (rank[i] > 0) {
      j = sa[rank[i] - 1];
      if (k) k--;
      while (i + k < n && j + k < n && r[i + k] == r[j + k]) k++;
    }
}

void BuildST(int n, int height[], vector<vector<int>>& st) {
  st.resize(n, vector<int>(20, 0));
  for (int i = 0; i < n; i++) {
    st[i][0] = height[i];
  }
  for (int j = 1; (1 << j) <= n; j++) {
    for (int i = 0; i + (1 << j) <= n; i++) {
      st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
  }
}

int sa[maxn * 3];      // 第几名的位置, 对应 sa
int rk[maxn * 3];      // 第几个元素排第几名, 对应 rk
int height[maxn * 3];  // 第几名与上一名的最长前缀, 对应 height
vector<vector<int>> st;
int r[maxn * 3];

inline int MaxBit(int v) { return 31 - __builtin_clz(v); }

void BuildHeight(char* str, int n, int sa[], int rk[], int height[]) {
  fill_n(height, n, 0);
  int k = 0;
  for (int i = 0; i < n - 1; i++) {  // 依次从最长的前缀开始处理
    int pi = rk[i];                  // s[i...n]; 的排名
    int j = sa[pi - 1];              // pi 上一名的位置
    while (str[i + k] == str[j + k]) k++;
    height[pi] = k;
    k = max(k - 1, 0);
  }
}

void BuildST(vector<int>& height, vector<vector<int>>& st) {
  int n = height.size();
  st.resize(n, vector<int>(20, 0));
  for (int i = 0; i < n; i++) {
    st[i][0] = height[i];
  }
  for (int j = 1; (1 << j) <= n; j++) {
    for (int i = 0; i + (1 << j) <= n; i++) {
      st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
  }
}

int Lcp(int i, int j) {
  const int n = st.size();
  if (i == j) return n - i;
  int ri = rk[i];
  int rj = rk[j];
  if (ri > rj) {
    swap(ri, rj);
  }
  int l = ri + 1;
  int r = rj + 1;
  int k = MaxBit(r - l);
  return min(st[l][k], st[r - (1 << k)][k]);
}
int LcpRk(int ri, int rj) {
  assert(ri <= rj);
  if (ri == rj) {
    return st.size() - sa[ri];
  }
  if (ri > rj) {
    swap(ri, rj);
  }
  int l = ri + 1;
  int r = rj + 1;
  int k = MaxBit(r - l);
  return min(st[l][k], st[r - (1 << k)][k]);
}

void BuildRA(char* str, int n, int m = 256) {                    //  m 为值域
  for (int i = 0; i < n; i++) r[i] = (unsigned char)str[i] + 1;  // 映射到 [1..m]
  da(r, sa, rk, height, n, m);
  BuildHeight(str, n, sa, rk, height);
  BuildST(n, height, st);
}

};  // namespace DC3

const int MAXN = 6e6 + 6;
int n, q;
ll ans[MAXN];

const char S3_TOP = '(';     // 40
const char T3_MIDDLE = '?';  // 63
const char S3_BOTTOM = '}';  // 125
const char S3_JOIN = '$';    // 35
const char BUF_END = '#';    // 32
char baseBuf[MAXN];
int baseBufLen = 0;
char buf[MAXN*3];
int bufLen = 0;
char s1[MAXN], s2[MAXN];
string_view MergeS1S2(const int len) {
  int leftLen = 0, rightLen = len - 1;  // [leftLen, rightLen] 是不同的区间
  while (leftLen < len && s1[leftLen] == s2[leftLen]) {
    leftLen++;
  }
  while (rightLen >= 0 && s1[rightLen] == s2[rightLen]) {
    rightLen--;
  }

  int mergeLen = 0;
  char* s3 = baseBuf + baseBufLen;
  // s1[0, leftLen-1] +
  for (int i = 0; i < leftLen; i++) {
    s3[mergeLen++] = s1[i];
  }
  // '1' + s1[leftLen, rightLen] +
  s3[mergeLen++] = S3_JOIN;
  for (int i = leftLen; i <= rightLen; i++) {
    s3[mergeLen++] = s1[i];
  }
  // '2' + s2[leftLen, rightLen] +
  s3[mergeLen++] = S3_JOIN;
  for (int i = leftLen; i <= rightLen; i++) {
    s3[mergeLen++] = s2[i];
  }
  // '3'+  s2[rightLen+1, len-1] +
  s3[mergeLen++] = S3_JOIN;
  for (int i = rightLen + 1; i < len; i++) {
    s3[mergeLen++] = s2[i];
  }
  s3[mergeLen] = '\0';
  baseBufLen += (mergeLen + 1);
  return string_view(s3, mergeLen);
}

struct SInfo {
  string_view s;
  int offset1;
};
struct TInfo {
  string_view t;
  int offsetLeft, offsetRight;
  int flag;
  int idx;
};
SInfo patterns[max5];
TInfo queries[max5];
int differenceArray[MAXN * 2];
int queryOffset[MAXN * 2];
void PreInit() {  // 不应该计算耗时
  baseBufLen = 0;
}
void Solver() {  //
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) {
    scanf("%s%s", s1, s2);
    int len = strlen(s1);
    auto s3 = MergeS1S2(len);
    patterns[i].s = s3;
  }

  // q 个询问
  for (int i = 0; i < q; i++) {
    scanf("%s%s", s1, s2);
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 != len2) {      // 长度不同，直接输出 0
      queries[i].flag = -1;  // 代表无效查询
      continue;
    }
    auto s3 = MergeS1S2(len1);
    queries[i].t = s3;
    queries[i].flag = 1;  // 代表有效查询
    queries[i].idx = i;
  }

  bufLen = 0;
  for (int i = 0; i < n; i++) {
    patterns[i].offset1 = bufLen;
    for (auto c : patterns[i].s) {
      buf[bufLen++] = c;
    }
    buf[bufLen++] = S3_TOP;
  }
  for (int i = 0; i < q; i++) {
    if (queries[i].flag == -1) continue;  // 无效查询
    queries[i].offsetLeft = bufLen;
    for (auto c : queries[i].t) {
      buf[bufLen++] = c;
    }
    buf[bufLen++] = T3_MIDDLE;
    queries[i].offsetRight = bufLen;
  }

  buf[bufLen++] = BUF_END;  // 结尾追增独一无二的字符，保证后缀数组正确性
  buf[bufLen] = '\0';
  MyPrintf("buf=%s\n", buf);

  memset(queryOffset, -1, sizeof(queryOffset[0]) * bufLen);
  for (int i = 0; i < q; i++) {
    if (queries[i].flag == -1) continue;  // 无效查询
    MyPrintf("i=%d t=[%s] offsetRange[%d, %d) \n", i, queries[i].t.data(), queries[i].offsetLeft,
             queries[i].offsetRight);
    queryOffset[i] = queries[i].offsetLeft;
  }

  DC3::BuildRA(buf, bufLen);
  auto FindR1 = [&](const int l1, const int len) -> int {
    int l = 0, r = l1;  // (l, r]
    while (l < r) {
      int mid = (l + r) / 2;
      int lcp = DC3::LcpRk(mid, l1);
      if (lcp >= len) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l;
  };
  auto FindR2 = [&](const int r1, const int len) -> int {
    int l = r1, r = bufLen;  //[l, r)
    while (l < r) {
      int mid = (l + r) / 2;
      int lcp = DC3::LcpRk(r1, mid);
      if (lcp >= len) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return r - 1;
  };
  for (int i = 0; i < n; i++) {
    int pr = DC3::rk[patterns[i].offset1];
    int r1 = FindR1(pr, patterns[i].s.length());
    int r2 = FindR2(pr, patterns[i].s.length());
    // r1 一定小于 r2
    assert(r1 <= r2);
    MyPrintf("i=%d s=[%s] offset1=%d r1=%d r2=%d\n", i, patterns[i].s.data(), patterns[i].offset1, r1, r2);
    if (r1 < r2) {
      differenceArray[r1]++;
      differenceArray[r2 + 1]--;
    }
  }

  memset(ans, 0, sizeof(ans[0]) * q);

  auto FindIdx = [&](int offset) {  //
    int i = upper_bound(queryOffset, queryOffset + q, offset) - queryOffset;
    if (i == 0) return -1;
    i--;
    auto& query = queries[i];
    if (offset >= query.offsetLeft && offset < query.offsetRight) {
      return query.idx;
    }
    return -1;
  };
  int preSum = 0;
  for (int rank = 0; rank < bufLen; rank++) {
    int offset = DC3::sa[rank];
    preSum += differenceArray[rank];
    if (preSum == 0) continue;  // 剪枝
    differenceArray[rank] = 0;
    int queryIdx = FindIdx(offset);
    MyPrintf("rank=%d sum=%d  offset=%d idx=%d\n", rank, preSum, offset, queryIdx);
    if (queryIdx == -1) continue;  // 无效查询
    ans[queryIdx] += preSum;
  }
  differenceArray[bufLen] = 0;
  differenceArray[bufLen + 1] = 0;
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