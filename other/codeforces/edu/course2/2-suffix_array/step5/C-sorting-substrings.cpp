/*
ID: tiankonguse
TASK: C. Sorting Substrings  C. 子串排序
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/C
PATH: ITMO 学院：试点课程 » 后缀数组 » 步骤5 » 实践
submission: https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/submission/298136389
*/
#define TASK "C-sorting-substrings"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK TASKEX);
#endif
}

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

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

/*
线段树：区间单点更新，修改查询
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
struct SegTree {
  vector<pair<ll, int>> minVal;  // 记录最值的位置
  vector<pair<ll, ll>> ranges;
  vector<ll> str;

  void Init(vector<int>& str_, const ll default_val = 0) {
    maxNM = str_.size() + 1;
    minVal.resize(maxNM << 2);
    ranges.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1, default_val);
    for (int i = 0; i < str_.size(); i++) {
      str[i + 1] = str_[i];
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
  }
  int Num(pair<ll, ll> p) { return p.second - p.first + 1; }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    ranges[rt] = {l, r};
    if (l == r) {
      minVal[rt] = {str[l], l};
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  pair<ll, int> QueryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    int m = (l + r) >> 1;
    pair<ll, int> ret = {__LONG_LONG_MAX__, 0};  // 求最小值，初始值设置为最大值
    if (L <= m) {
      ret = min(ret, QueryMin(L, R, lson));
    }
    if (m < R) {
      ret = min(ret, QueryMin(L, R, rson));
    }
    return ret;
  }
};

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

void SuffixArray(char* str, int n, vector<int>& p, vector<int>& c) {
  vector<pair<pair<int, int>, int>> nums(n);

  cnt.resize(n, 0);
  pos.resize(n, 0);
  tmpNums.resize(n);

  p.resize(n, 0);
  c.resize(n, 0);

  for (int k = 0; 1 << max(k - 1, 0) < n; k++) {
    for (int j = 0; j < n; j++) {
      pair<int, int> v;
      if (k > 0) {
        int leftRank = c[j];
        int rightRank = c[(j + (1 << (k - 1))) % n];
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
      p[j] = nums[j].second;  // 排名第 j 的位置
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
      c[pos] = rank;  // 第pos个值的排名
    }
    if (rank + 1 == n) break;  // 剪枝，已经没有重复了
  }
}

void Lcp(char* str, int n, vector<int>& p, vector<int>& c, vector<int>& lcp) {
  lcp.resize(n, 0);
  int k = 0;
  for (int i = 0; i < n - 1; i++) {  // 依次从最长的前缀开始处理
    int pi = c[i];                   // s[i...n]; 的排名
    int j = p[pi - 1];               // pi 上一名的位置
    while (str[i + k] == str[j + k]) k++;
    lcp[pi] = k;
    k = max(k - 1, 0);
  }
}

vector<int> P;    // 第几名的位置, 对应 sa
vector<int> C;    // 第几个元素排第几名, 对应 rk
vector<int> lcp;  // 第几名与上一名的最长前缀, 对应 height

const int N = 4e5 + 10;
char str[N];
int n;
int t;
vector<pair<int, int>> nums;
void InitIO() {
  // #ifdef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
  scanf("%s", str);
}

SegTree segTree;
int Lcp(int rk1, int rk2) {  // 线段树查询区间最小值
  if (rk1 > rk2) {
    swap(rk1, rk2);
  }
  if (rk1 + 1 == rk2) {
    return lcp[rk2];
  }
  return segTree.QueryMin(rk1 + 2, rk2 + 1).first;
}

void Solver() {  //
  n = strlen(str);
  str[n++] = 32;
  str[n] = '\0';
  SuffixArray(str, n, P, C);
  Lcp(str, n, P, C, lcp);

  // for (int r = 0; r < n; r++) {
  //   printf("p=%d r=%d lcp=%d v=[%s]\n", P[r], r, lcp[r], str + P[r]);
  // }

  segTree.Init(lcp);
  segTree.Build();

  scanf("%d", &t);
  nums.resize(t);
  for (int i = 0; i < t; i++) {
    scanf("%d%d", &nums[i].first, &nums[i].second);
  }
  sort(nums.begin(), nums.end(), [](const auto& p1, const auto& p2) -> bool {
    auto [l1, r1] = p1;
    auto [l2, r2] = p2;
    if (l1 == l2) {  // 相同前缀
      return r1 < r2;
    }
    int rk1 = C[l1 - 1], n1 = r1 - l1 + 1;
    int rk2 = C[l2 - 1], n2 = r2 - l2 + 1;
    int pre = Lcp(rk1, rk2);
    // printf("[%d,%d]=%d vs [%d,%d]=%d: rk1=%d rk2=%d pre=%d\n", l1, r1, n1,
    // l2,
    //        r2, n2, rk1, rk2, pre);
    if (n1 > pre && n2 > pre) {  // 大小是明确的
      return rk1 < rk2;
    }
    if (n1 == n2) {
      return l1 < l2;  // 相等, 先位置排序
    } else {
      return n1 <= n2;  // 不相等，谁短谁在前面
    }
  });
  // for (int i = 0; i < t; i++) {
  //   auto [l, r] = nums[i];
  //   printf("%d %d %s\n", l, r, string(str + l - 1, (r - l + 1)).data());
  // }
  for (int i = 0; i < t; i++) {
    auto [l, r] = nums[i];
    printf("%d %d\n", l, r);
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my =
      std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(
          t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/