/*
ID: tiankonguse
TASK: replace
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
注：分组求SA,使用树状数组代替差分数组
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

  cnt.clear();
  cnt.resize(n, 0);
  pos.clear();
  pos.resize(n, 0);
  tmpNums.clear();
  tmpNums.resize(n);

  sa.clear();
  sa.resize(n, 0);
  rk.clear();
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
  height.clear();
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
  // BuildHeight(str, n);
  // BuildST();
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
ll ans[MAXN];

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
  int offset1, offset2;
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
int queryOffset[MAXN * 2];
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

void SolverGroup(STInfo& info) {
  auto& patterns = info.patterns;
  auto& queries = info.queries;
  BuildRaBuf(info);
  MyPrintf("buf=%s\n", buf);
  const int totalLen = bufLen;

  // 先使用数组来计算 queryOffset
  // 如果超时，考虑使用二分查找
  // 复杂度：O(L) -> O(q log(q))
  memset(queryOffset, -1, sizeof(queryOffset[0]) * totalLen);
  memset(differenceArray, 0, sizeof(differenceArray[0]) * (totalLen + 2));
  for (auto& query : queries) {
    MyPrintf("i=%d t=%s offsetRange[%d, %d) \n", query.idx, query.s.c_str(), query.offsetLeft, query.offsetRight);
    for (int o = query.offsetLeft; o < query.offsetRight; o++) {
      queryOffset[o] = query.idx;
    }
  }

  SA::BuildRA(buf, totalLen);
  for (auto& pattern : patterns) {
    int r1 = SA::rk[pattern.offset1];
    int r2 = SA::rk[pattern.offset2];
    // r1 一定小于 r2
    assert(r1 < r2);
    MyPrintf("s=%s offset1=%d offset2=%d r1=%d r2=%d\n", pattern.s.c_str(), pattern.offset1, pattern.offset2, r1, r2);
    differenceArray[r1]++;
    differenceArray[r2 + 1]--;
  }
  int preSum = 0;
  for (int rank = 0; rank < totalLen; rank++) {
    preSum += differenceArray[rank];
    int offset = SA::sa[rank];
    int queryIdx = queryOffset[offset];
    if (preSum != 0) {
      MyPrintf("rank=%d sum=%d  offset=%d idx=%d\n", rank, preSum, offset, queryIdx);
    }
    if (queryIdx == -1) continue;  // 无效查询
    ans[queryIdx] += preSum;
  }
}

void Solver() {  //
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) {
    scanf("%s%s", s1, s2);
    int len = strlen(s1);
    MergeS1S2(len);
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
  printf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
#endif
  return 0;
}

/*
case 1: Accepted, cost 0ms
case 2: Accepted, cost 0ms
case 3: Accepted, cost 1ms
case 4: Accepted, cost 1ms
case 5: Accepted, cost 1ms
case 6: Accepted, cost 1711ms
case 7: Accepted, cost 4012ms
case 8: Accepted, cost 3707ms
case 9: Accepted, cost 2192ms
case 10: Accepted, cost 2308ms
case 11: Accepted, cost 6463ms
case 12: Accepted, cost 7044ms
case 13: Accepted, cost 25454ms
case 14: Accepted, cost 25972ms
case 15: Accepted, cost 8614ms
case 16: Accepted, cost 8920ms
case 17: Accepted, cost 26488ms
case 18: Accepted, cost 25196ms
case 19: Accepted, cost 23906ms
case 20: Accepted, cost 26103ms
Total: 20 / 20, 得分： 100
*/