/*
ID: tiankonguse
TASK: F. Periodic Substring  F. 周期子串
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/F
PATH: ITMO 学院：试点课程 » 后缀数组 » 步骤5 » 实践
submission:
*/
#define TASK "F-periodic-substring"
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

void BuildHeight(char* str, int n, vector<int>& sa, vector<int>& rk,
                 vector<int>& height) {
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
ll Lcp(int i, int j) {
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

const int N = 4e5 + 10;
char str[N];
int n;
void InitIO() {
  // #ifdef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
  scanf("%s", str);
  n = strlen(str);
  str[n++] = '$';
  str[n] = '\0';
}

void Solver() {  //
  SuffixArray(str, n, sa, rk);
  BuildHeight(str, n, sa, rk, height);
  BuildST(height, st);

  int ans = 1;
  for (int l = 1; l < n; l++) {  // 枚举周期
    // 先找到以 0+k*l 为偏移量的每个前缀的最大周期，然后判断是否可以左滑部分，多得到一个周期
    for (int i = 0; i + l < n; i += l) {
      int repLen = Lcp(i, i + l);
      int repCnt = repLen / l + 1;
      if (int p = i - (l - repLen % l); p >= 0 && Lcp(p, p + l) >= l) {
        repCnt++;
      }
      ans = max(ans, repCnt);
    }
  }
  printf("%d\n", ans);
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