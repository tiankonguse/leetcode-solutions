/*
ID: tiankonguse
TASK: A. Suffix Array - 1 A. 后缀数组 - 1
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/2/1/practice/contest/269100/problem/A
PATH: ITMO 学院：试点课程 » 后缀数组 » 步骤1 » 实践
submission:
https://codeforces.com/edu/course/2/lesson/2/1/practice/contest/269100/submission/296870949
*/
#define TASK "demo"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

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

int LogN(int n) {
  int k = 1;
  int v = 0;
  while (n) {
    v += n & 1;
    n >>= 1;
    k++;
  }
  if (v > 1) {
    k++;
  }
  return k;
}

template <typename F>
void radix_sort_inner(vector<pair<pair<int, int>, int>>& nums,
                      const F& Callback) {
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

void radix_sort(vector<pair<pair<int, int>, int>>& nums) {
  radix_sort_inner(nums, [](const std::pair<int, int>& p) { return p.second; });
  radix_sort_inner(nums, [](const std::pair<int, int>& p) { return p.first; });
}

vector<pair<pair<int, int>, int>> nums;
int n;
void Solver() {
  n = strlen(str);
  str[n] = '$';
  n++;

  vector<int> p(n);  // 排名i的位置
  vector<int> c(n);  // 位置p的排名，多个位置相等时排名相同

  nums.resize(n);
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
      radix_sort(nums);
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

    // printf("i=%d\n", i);
    // for (int j = 0; j < n; j++) {
    //   printf("j=%d rank=%d\n", j, bt[i][j]);
    // }
  }

  for (int j = 0; j < n; j++) {
    printf("%d%c", p[j], j + 1 == n ? '\n' : ' ');
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
  InitIO();
  ExSolver();
  return 0;
}

/*

*/