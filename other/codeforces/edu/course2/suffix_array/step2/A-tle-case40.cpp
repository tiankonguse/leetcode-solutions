/*
ID: tiankonguse
TASK: A. Suffix Array - 2 A. 后缀数组 - 2
LANG: C++
MAC EOF: ctrl+D
link:
hhttps://codeforces.com/edu/course/2/lesson/2/2/practice/contest/269103/problem/A
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
  int k = 0;
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

vector<vector<int>> bt;
int n;
inline pair<int, int> LeftRightRank(int i, int j) {
  int leftRank = bt[i - 1][j];
  int rightRank = bt[i - 1][(j + (1 << (i - 1))) % n];
  return {leftRank, rightRank};
}
void Solver() {  //

  vector<int> nums;
  vector<vector<int>> nums2;
  vector<vector<int>> nums1;
  int nn = strlen(str);
  str[nn] = '$';
  nn++;
  n = nn;

  int K = LogN(n);
  bt.resize(K + 1, vector<int>(n, 0));

  nums.resize(n + 1);   // 计数排序
  nums2.resize(n + 1);  // 计数排序
  nums1.resize(n + 1);  // 计数排序

  vector<int> base(256);
  for (int j = 0; j < n; j++) {
    base[str[j]] = 1;
  }
  int rank = 0;
  for (auto& v : base) {
    if (v == 1) {
      v = ++rank;
    }
  }
  for (int j = 0; j < n; j++) {
    bt[0][j] = base[str[j]] - 1;
  }

  for (int i = 1; i <= K; i++) {
    for (int j = 0; j < n; j++) {
      nums2[j].clear();
    }
    int maxRightRank = 0;
    for (int j = 0; j < n; j++) {
      int rightRank = LeftRightRank(i, j).second;
      nums2[rightRank].push_back(j);
      maxRightRank = max(maxRightRank, rightRank);
    }

    for (int j = 0; j < n; j++) {
      nums1[j].clear();
    }

    int maxLeftRank = 0;
    for (int r = 0; r <= maxRightRank; r++) {
      for (auto j : nums2[r]) {
        int leftRank = LeftRightRank(i, j).first;
        nums1[leftRank].push_back(j);
        maxLeftRank = max(maxLeftRank, leftRank);
      }
    }

    // 最小的肯定是 $
    auto pre = LeftRightRank(i, nums1.front().front());
    int rank = 0;
    for (int r = 0; r <= maxLeftRank; r++) {
      for (auto j : nums1[r]) {
        auto v = LeftRightRank(i, j);
        if (v != pre) {
          pre = v;
          rank++;
        }
        bt[i][j] = rank;
      }
    }

    // printf("i=%d\n", i);
    // for (int j = 0; j < n; j++) {
    //   printf("j=%d rank=%d\n", j, bt[i][j]);
    // }
  }

  for (int j = 0; j < n; j++) {
    nums[bt[K][j]] = j;
  }
  for (int j = 0; j < n; j++) {
    printf("%d%c", nums[j], j + 1 == n ? '\n' : ' ');
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