/*
ID: tiankonguse
TASK: query
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "query"
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
线段树：单点更新，区间查询
特征：不需要延迟标记与PushDown，log(N)的更新时间复杂度

输入数组： vector<int> str; [0, n-1]

SegTree segTree;
segTree.Init(str); // 内部会对数组进行右移，转化为 [1,n]
segTree.Build();
segTree.Update(l, val); // 单点 l 都加上 val, 数据范围 [1,n]
segTree.QueryMax/QueryMin/QuerySum 区间查询, 数据范围 [1,n]
*/

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
typedef long long ull;
struct SegTree {
  vector<pair<ll, int>> maxVal;  // 记录最值的位置
  vector<ll> str;

  void Init(vector<ll>& str_, const ll default_val = 0) {
    maxNM = str_.size() + 1;
    maxVal.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1, default_val);
    for (int i = 1; i < str_.size(); i++) {
      str[i] = str_[i];
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
  }
  int Num(pair<ll, ll> p) { return p.second - p.first + 1; }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      maxVal[rt] = {str[l], l};
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, ll setVal, int l = 1, int r = maxNM, int rt = 1) {
    if (L == l && r == L) {
      maxVal[rt].first = setVal;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, setVal, lson);
    if (L > m) Update(L, setVal, rson);
    PushUp(rt, l, r);
  }
  pair<ll, int> QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxVal[rt];
    }
    int m = (l + r) >> 1;
    pair<ll, int> ret = {INT64_MIN, 0};
    if (L <= m) {
      ret = max(ret, QueryMax(L, R, lson));
    }
    if (m < R) {
      ret = max(ret, QueryMax(L, R, rson));
    }
    return ret;
  }
};

int n, q;
vector<ll> preSums;
vector<ll> sufSums;
vector<ll> nums;
SegTree segTreePre;
SegTree segTreeSuf;
SegTree segTreeTmp;

// dpL[i] = max(sums[i,L], ..., sums[i,R])
// dpLL[i] = max(dpL[i-L+1], ..., dpL[i]);
vector<ll> dpL;  // dpL[i]: 以 i 为左端点的所有极好区间的最大权值
vector<ll> dpR;  // dpR[i]: 以 i 为右端点的所有极好区间的最大权值
__int128_t pow2_64 = (__int128_t(1) << 64);

ull Fix(ll k) {
  ull kk = 0;
  if (k < 0) {
    __int128_t t = k;
    t += pow2_64;
    kk = t;
  } else {
    kk = k;
  }
  return kk;
}

ull Solver(int L, int R) {
  dpL.resize(n + 1, 0);
  for (int l = 1; l <= n; l++) {
    int rL = l + L - 1;
    int rR = l + R - 1;
    // [l, rL] ... [l, rR]
    if (rL > n) {  // 没有答案
      dpL[l] = INT64_MIN;
    } else {
      rR = min(rR, n);
      dpL[l] = segTreePre.QueryMax(rL, rR).first - preSums[l - 1];
    }
    MyPrintf("l=%d, rL=%d rR=%d, dpL[l]=%lld\n", l, rL, rR, dpL[l]);
    segTreeTmp.Update(l, dpL[l]);
  }
  for (int i = 1; i <= n; i++) {
    int left = max(i - L + 1, 1);
    dpL[i] = segTreeTmp.QueryMax(left, i).first;
    MyPrintf("i=%d, max(dpL[%d, %d])=%lld\n", i, left, i, dpL[i]);
  }

  dpR.resize(n + 1, 0);
  for (int r = n; r >= 1; r--) {
    int lR = r - L + 1;
    int lL = r - R + 1;
    if (lR < 1) {  // 没有答案
      dpR[r] = INT64_MIN;
    } else {
      lL = max(lL, 1);
      dpR[r] = segTreeSuf.QueryMax(lL, lR).first - sufSums[r + 1];
    }
    MyPrintf("r=%d, lL=%d lR=%d dpR[r]=%lld\n", r, lL, lR, dpR[r]);
    segTreeTmp.Update(r, dpR[r]);
  }
  for (int i = n; i >= 1; i--) {
    int right = min(i + L - 1, n);
    dpR[i] = segTreeTmp.QueryMax(i, right).first;
    MyPrintf("i=%d, max(dpR[%d, %d])=%lld\n", i, i, right, dpR[i]);
  }

  ull ans = 0;
  for (int i = 1; i <= n; i++) {
    ll k = max(dpL[i], dpR[i]);
    MyPrintf("i=%d, k=%lld, dpL=%lld dpR=%lld\n", i, k, dpL[i], dpR[i]);
    ans ^= Fix(k * i);
  }

  return ans;
}
void Init() {
  preSums.resize(n + 2, 0);
  segTreeTmp.Init(preSums);
  segTreeTmp.Build();

  preSums[0] = 0;
  for (int i = 1; i <= n; i++) {
    preSums[i] = preSums[i - 1] + nums[i];
  }
  for (int i = 0; i <= n; i++) {
    MyPrintf("i=%d, preSums[i]=%lld\n", i, preSums[i]);
  }

  segTreePre.Init(preSums);
  segTreePre.Build();

  sufSums.resize(n + 2, 0);
  sufSums[n + 1] = 0;
  for (int i = n; i >= 1; i--) {
    sufSums[i] = sufSums[i + 1] + nums[i];
  }
  for (int i = n + 1; i >= 1; i--) {
    MyPrintf("i=%d, sufSums[i]=%lld\n", i, sufSums[i]);
  }
  segTreeSuf.Init(sufSums);
  segTreeSuf.Build();
}
void Solver() {  //
  scanf("%d", &n);
  nums.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &nums[i]);
  }
  Init();
  scanf("%d", &q);
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    printf("%llu\n", Solver(l, r));
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
