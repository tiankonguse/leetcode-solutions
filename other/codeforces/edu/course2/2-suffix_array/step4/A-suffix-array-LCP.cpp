/*
ID: tiankonguse
TASK: A. Suffix Array and LCP A. 后缀数组和LCP
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/2/4/practice/contest/269119/problem/A
PATH: ITMO 学院：试点课程 » 后缀数组 » 步骤4 » 实践
submission:
*/
#define TASK "A-suffix-array-LCP"
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

const int N = 4e5 + 10;
char str[N];
void InitIO() {  //
  scanf("%s", str);
}

template <typename F>
void radix_sort(vector<pair<pair<int, int>, int>>& nums, const F& Callback) {
  const int n = nums.size();
  vector<int> cnt(n, 0);
  for (auto& x : nums) {
    cnt[Callback(x.first)]++;
  }

  vector<int> pos(n, 0);  // 排名为 i 时，累计个数
  for (int r = 1; r < n; r++) {
    pos[r] = pos[r - 1] + cnt[r - 1];
  }

  vector<pair<pair<int, int>, int>> tmp(n);
  for (auto& x : nums) {
    int r = Callback(x.first);
    tmp[pos[r]] = x;
    pos[r]++;
  }
  tmp.swap(nums);
}

void SuffixArray(char* str, int n, vector<int>& p, vector<int>& c) {
  vector<pair<pair<int, int>, int>> nums(n);
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
vector<int> lcp;  // 相邻元素最长前缀, 对应 height

int n;
void Init() {
  n = strlen(str);
  str[n] = '$';
  n++;
  str[n] = '\0';
  SuffixArray(str, n, P, C);
  Lcp(str, n, P, C, lcp);
}
void Solver() {  //
  Init();
  for (int i = 0; i < n; i++) {
    printf("%d%c", P[i], i + 1 == n ? '\n' : ' ');
  }
  for (int i = 1; i < n; i++) {
    printf("%d%c", lcp[i], i + 1 == n ? '\n' : ' ');
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