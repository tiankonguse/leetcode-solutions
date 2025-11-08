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
#define TASKEX "-ra"

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
#define USACO_TASK_FILE 20
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

namespace SA {

vector<int> cnt;
vector<int> pos;
vector<pair<pair<int, int>, int>> tmpNums;
template <typename F>
void radix_sort(vector<pair<pair<int, int>, int>>& nums, const F& Callback) {
  const int n = nums.size();
  for (auto& x : nums) {
    cnt[Callback(x.first)]++;
  }

  pos[0] = 0;  // 排名为 i 时，累计个数
  for (int r = 1; r < n; r++) {
    pos[r] = pos[r - 1] + cnt[r - 1];
  }

  for (auto& x : nums) {
    cnt[Callback(x.first)]--;  // 使用完了，还原数组
  }

  for (auto& x : nums) {
    int r = Callback(x.first);
    tmpNums[pos[r]] = x;
    pos[r]++;
  }
  tmpNums.swap(nums);
}

void SuffixArray(char* str, int n, vector<int>& sa, vector<int>& rk) {
  vector<pair<pair<int, int>, int>> nums(n);

  cnt.resize(n, 0);
  pos.resize(n, 0);
  tmpNums.resize(n);

  sa.resize(n, 0);
  rk.resize(n, 0);

  for (int k = 0; 1 << max(k - 1, 0) < n; k++) {
    for (int j = 0; j < n; j++) {
      pair<int, int> v;
      if (k > 0) {
        int leftRank = rk[j];
        int rightRank = rk[(j + (1 << (k - 1))) % n];
        v = {leftRank, rightRank};
      } else {
        v = {str[j], 0};  // 第一次，只需要对一个值排序
      }
      nums[j] = {v, j};
    }
    if (k == 0) {
      sort(nums.begin(), nums.end());
    } else {
      radix_sort(nums, [](const std::pair<int, int>& p) { return p.second; });
      radix_sort(nums, [](const std::pair<int, int>& p) { return p.first; });
    }

    for (int j = 0; j < n; j++) {
      sa[j] = nums[j].second;  // 排名第 j 的位置
    }

    // 最小的肯定是 $
    auto pre = nums.front().first;
    int rank = 0;
    for (int j = 0; j < n; j++) {
      auto [v, pos] = nums[j];
      if (v != pre) {
        pre = v;
        rank++;
      }
      rk[pos] = rank;  // 第pos个值的排名
    }
    if (rank + 1 == n) break;  // 剪枝，已经没有重复了
  }
}

void BuildHeight(char* str, int n, vector<int>& sa, vector<int>& rk, vector<int>& height) {
  height.resize(n, 0);
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

vector<int> sa;      // 第几名的位置, 对应 sa
vector<int> rk;      // 第几个元素排第几名, 对应 rk
vector<int> height;  // 第几名与上一名的最长前缀, 对应 height
vector<vector<int>> st;
inline int MaxBit(int v) { return 31 - __builtin_clz(v); }

void SuffixArray(char* str, int n) { SuffixArray(str, n, sa, rk); }
void BuildHeight(char* str, int n) { BuildHeight(str, n, sa, rk, height); }
void BuildST() { BuildST(height, st); }

void BuildRA(char* str, int n) {
  SuffixArray(str, n);
  BuildHeight(str, n);
  BuildST();
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
// SuffixArray(str, n, sa, rk);
// BuildHeight(str, n, sa, rk, height);
// BuildST(height, st);
};  // namespace SA

const int MAXN = 6e6 + 6;
int n, q;
ll ans[MAXN];

char s1[MAXN], s2[MAXN], s3[MAXN];
int s3Len = 0;
void MergeS1S2(const int len) {
  int leftLen = 0, rightLen = len - 1;  // [leftLen, rightLen] 是不同的区间
  while (leftLen < len && s1[leftLen] == s2[leftLen]) {
    leftLen++;
  }
  while (rightLen >= 0 && s1[rightLen] == s2[rightLen]) {
    rightLen--;
  }

  int mergeLen = 0;
  // s1[0, leftLen-1] +
  for (int i = 0; i < leftLen; i++) {
    s3[mergeLen++] = s1[i];
  }
  // '1' + s1[leftLen, rightLen] +
  s3[mergeLen++] = ' ';
  for (int i = leftLen; i <= rightLen; i++) {
    s3[mergeLen++] = s1[i];
  }
  // '2' + s2[leftLen, rightLen] +
  s3[mergeLen++] = ' ';
  for (int i = leftLen; i <= rightLen; i++) {
    s3[mergeLen++] = s2[i];
  }
  // '3'+  s2[rightLen+1, len-1] +
  s3[mergeLen++] = ' ';
  for (int i = rightLen + 1; i < len; i++) {
    s3[mergeLen++] = s2[i];
  }
  s3[mergeLen] = '\0';
  s3Len = mergeLen;
}

struct SInfo {
  string s;
  int offset1, offset2;
};
struct TInfo {
  string t;
  int offsetLeft, offsetRight;
  int flag;
};
SInfo patterns[max5];
TInfo queries[max5];
int differenceArray[MAXN * 2];
int queryOffset[MAXN * 2];
char buf[MAXN * 2];
int bufLen = 0;

// S(最小): S3 + '('
// T(大于S): T3 + '?'
// S(大于T): S3 + '}'
const char S3_TOP = '(';
const char T3_MIDDLE = '?';
const char S3_BOTTOM = '}';
const char BUF_END = '$';
void Solver() {  //
  scanf("%d%d", &n, &q);
  bufLen = 0;
  for (int i = 0; i < n; i++) {
    scanf("%s%s", s1, s2);
    int len = strlen(s1);
    MergeS1S2(len);

    patterns[i].offset1 = bufLen;
    for (int j = 0; j < s3Len; j++) {
      buf[bufLen++] = s3[j];
    }
    buf[bufLen++] = S3_TOP;

    patterns[i].offset2 = bufLen;
    for (int j = 0; j < s3Len; j++) {
      buf[bufLen++] = s3[j];
    }
    buf[bufLen++] = S3_BOTTOM;
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
    MergeS1S2(len1);
    queries[i].flag = 1;  // 代表有效查询
    queries[i].offsetLeft = bufLen;
    for (int j = 0; j < s3Len; j++) {
      buf[bufLen++] = s3[j];
    }
    buf[bufLen++] = T3_MIDDLE;
    queries[i].offsetRight = bufLen;
  }
  buf[bufLen++] = BUF_END;
  buf[bufLen] = '\0';

  MyPrintf("buf=%s\n", buf);

  const int totalLen = bufLen;
  memset(queryOffset, -1, sizeof(queryOffset[0]) * totalLen);
  for (int i = 0; i < q; i++) {
    if (queries[i].flag == -1) continue;  // 无效查询
    MyPrintf("i=%d t=%s offsetRange[%d, %d) \n", i, queries[i].t.c_str(), queries[i].offsetLeft,
             queries[i].offsetRight);
    for (int o = queries[i].offsetLeft; o < queries[i].offsetRight; o++) {
      queryOffset[o] = i;
    }
  }

  SA::BuildRA(buf, totalLen);
  for (int i = 0; i < n; i++) {
    int r1 = SA::rk[patterns[i].offset1];
    int r2 = SA::rk[patterns[i].offset2];
    // r1 一定小于 r2
    assert(r1 < r2);
    MyPrintf("i=%d s=%s offset1=%d offset2=%d r1=%d r2=%d\n", i, patterns[i].s.c_str(), patterns[i].offset1,
             patterns[i].offset2, r1, r2);
    differenceArray[r1]++;
    differenceArray[r2 + 1]--;
  }

  // 差分转前缀和
  for (int rank = 1; rank <= totalLen; rank++) {
    differenceArray[rank] += differenceArray[rank - 1];
    // if (differenceArray[rank] != 0) {
    //   int offset = SA::sa[rank];
    //   MyPrintf("rank=%d sum=%d  offset=%d idx=%d\n", rank, differenceArray[rank], offset, queryOffset[offset]);
    // }
  }

  memset(ans, 0, sizeof(ans[0]) * q);
  for (int rank = 0; rank < totalLen; rank++) {
    int offset = SA::sa[rank];
    int queryIdx = queryOffset[offset];
    if (queryIdx == -1) continue;  // 无效查询
    ans[queryIdx] += differenceArray[rank];
  }
  for (int i = 0; i < q; i++) {
    printf("%lld\n", ans[i]);
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
  int AC = 0;
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    int fileIndex = i;
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
  printf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
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