/*
ID: tiankonguse
TASK: replace
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
注：全局求SA,使用树状数组代替差分数组
*/
#define TASK "replace"
#define TASKEX "-ra-70-da-lcp"

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
const int maxn = 2e7 + 10;
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

int sa[maxn];      // 第几名的位置, 对应 sa
int rk[maxn];      // 第几个元素排第几名, 对应 rk
int height[maxn];  // 第几名与上一名的最长前缀, 对应 height
vector<vector<int>> st;

inline int MaxBit(int v) { return 31 - __builtin_clz(v); }
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

void BuildRA(char* str, int n, int m = 256) {  //  m 为值域
  da(str, sa, rk, height, n, m);
  BuildST(n, height, st);
}
};  // namespace DA

namespace FENWICK {
class TreeArrayEx {
 public:
  void Init(int n_) {
    n = n_ + 1;
    t1.clear();
    t1.resize(n + 10, 0);
    t2.clear();
    t2.resize(n + 10, 0);
  }

  void AddEx(int l, int r, ll v) {
    Add(l, v);
    Add(r + 1, -v);  // 将区间加差分为两个前缀加
  }

  ll Query(int l, int r) {
    return (r + 1ll) * Query(t1, r) - 1ll * l * Query(t1, l - 1) - (Query(t2, r) - Query(t2, l - 1));
  }

 private:
  void Add(int k, ll v) {
    ll v1 = k * v;
    while (k <= n) {
      t1[k] += v, t2[k] += v1;
      k += Lowbit(k);
    }
  }
  ll Query(vector<ll>& t, int k) {
    ll ret = 0;
    while (k) {
      ret += t[k];
      k -= Lowbit(k);
    }
    return ret;
  }
  int Lowbit(int x) { return x & -x; }
  vector<ll> t1, t2;
  int n;
};
}  // namespace FENWICK

const int MAXN = 6e6 + 6;
int n, q;
ll ans[max5];

char s1[MAXN], s2[MAXN], s3[MAXN];
int s3Len = 0;
ll MergeS1S2(int len) {
  int leftLen = 0, rightLen = len - 1;  // [leftLen, rightLen] 是不同的区间
  int mergeLen = 0;
  while (leftLen < len && s1[leftLen] == s2[leftLen]) {
    s3[mergeLen++] = s1[leftLen];
    leftLen++;
  }
  s3[mergeLen++] = '#';
  while (rightLen >= 0 && s1[rightLen] == s2[rightLen]) {
    s3[mergeLen++] = s1[rightLen];
    rightLen--;
  }
  // 翻转 s3 的后半部分 [rightLen+1, mergeLen-1]
  std::reverse(s3 + leftLen + 1, s3 + mergeLen);
  s3[mergeLen] = '\0';
  s3Len = mergeLen;

  ll h = HASH::Hash(s1, leftLen, rightLen + 1);
  h = HASH::Hash(h, ' ');
  h = HASH::Hash(h, s2, leftLen, rightLen + 1);
  return h;
}
struct SInfo {
  string s;
  int offset1;
};
struct TInfo {
  string s;
  int idx;
  int offsetLeft, offsetRight;
};
struct STInfo {
  vector<SInfo> patterns;
  vector<TInfo> queries;
};

unordered_map<ll, STInfo> mp;

int differenceArray[MAXN * 2];
// int queryOffset[MAXN * 2];
int queryOffset[max5];
char buf[MAXN * 2];
int bufLen = 0;
// FENWICK::TreeArrayEx fenwick;

// S(最小): S3 + '('
// T(大于S): T3 + '?'
// S(大于T): S3 + '}'
const char S3_TOP = '(';
const char T3_MIDDLE = '?';
const char S3_BOTTOM = '}';
const char BUF_END = '$';
void BuildRaBuf(STInfo& info) {
  auto& patterns = info.patterns;
  auto& queries = info.queries;
  // S+'('
  // T + '?'
  bufLen = 0;
  for (auto& pattern : patterns) {
    pattern.offset1 = bufLen;
    for (auto c : pattern.s) {
      buf[bufLen++] = c;
    }
    buf[bufLen++] = S3_TOP;
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

void SolverGroup(STInfo& info) {
  auto& patterns = info.patterns;
  auto& queries = info.queries;
  const int qn = queries.size();
  BuildRaBuf(info);
  MyPrintf("buf=%s\n", buf);
  const int totalLen = bufLen;

  // 先使用数组来计算 queryOffset
  // 如果超时，考虑使用二分查找
  // 复杂度：O(L) -> O(q log(q))
  // fenwick.Init(totalLen + 10);
  // memset(queryOffset, -1, sizeof(queryOffset[0]) * totalLen);
  memset(differenceArray, 0, sizeof(differenceArray[0]) * (totalLen + 2));
  for (int i = 0; i < qn; i++) {
    auto& query = queries[i];
    MyPrintf("i=%d t=%s offsetRange[%d, %d) \n", query.idx, query.s.c_str(), query.offsetLeft, query.offsetRight);
    queryOffset[i] = query.offsetLeft;
    // for (int o = query.offsetLeft; o < query.offsetRight; o++) {
    //   queryOffset[o] = query.idx;
    // }
  }

  DA::BuildRA(buf, totalLen);
  auto FindR2 = [&](const int r1, const int len) -> int {
    int l = r1, r = totalLen;
    while (l < r) {
      int mid = (l + r) / 2;
      int lcp = DA::LcpRk(r1, mid);
      if (lcp >= len) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return r - 1;
  };
  for (auto& pattern : patterns) {
    int r1 = DA::rk[pattern.offset1];
    // 二分找到 r2, 满足 DA::lcp(r1, r2) >= pattern.s.length()
    int r2 = FindR2(r1, pattern.s.length());
    // r1 一定小于 r2
    assert(r1 <= r2);
    MyPrintf("s=%s offset1=%d r1=%d r2=%d\n", pattern.s.c_str(), pattern.offset1, r1, r2);
    // fenwick.AddEx(r1, r2, 1);
    r1++;  // 自己排除掉
    // r2--;
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
  for (int rank = 0; rank < totalLen; rank++) {
    preSum += differenceArray[rank];
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
}

void Solver() {  //
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) {
    scanf("%s%s", s1, s2);
    int len = strlen(s1);
    ll h = MergeS1S2(len);
    mp[h].patterns.resize(mp[h].patterns.size() + 1);
    auto& patternInfo = mp[h].patterns.back();
    patternInfo.s = s3;
    MyPrintf("i=%d h=%lld s=%s\n", i, h, patternInfo.s.c_str());
  }

  // q 个询问
  for (int i = 0; i < q; i++) {
    scanf("%s%s", s1, s2);
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 != len2) {
      continue;  // 长度不同，直接输出 0
    }
    ll h = MergeS1S2(len1);
    if (mp.count(h) == 0) {
      continue;  // 不存在该模式串，直接输出 0
    }

    mp[h].queries.resize(mp[h].queries.size() + 1);
    auto& queryInfo = mp[h].queries.back();
    queryInfo.s = s3;
    queryInfo.idx = i;
    MyPrintf("i=%d h=%lld t=%s\n", i, h, queryInfo.s.c_str());
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
    AC++;
    printf("case %d: Accepted, cost %.0lfms\n", i, costTime);
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
4 2
xabcx xadex
ab cd
bc de
aa bb
xabcx xadex
aaaa bbbb
buf=xa bc de x(xa bc de x} ab cd ( ab cd } bc de ( bc de } aa bb ( aa bb }xa bc de x? aaaa bbbb ?$
i=0 s=xa bc de x offset1=0 offset2=11 r1=86 r2=88
i=1 s= ab cd  offset1=22 offset2=30 r1=7 r2=8
i=2 s= bc de  offset1=38 offset2=46 r1=12 r2=16
i=3 s= aa bb  offset1=54 offset2=62 r1=4 r2=5

xa bc de x(
xa bc de x}
 ab cd (
 ab cd }
 bc de (
 bc de }
 aa bb (
 aa bb }
xa bc de x?
 aaaa bbbb ?
*/