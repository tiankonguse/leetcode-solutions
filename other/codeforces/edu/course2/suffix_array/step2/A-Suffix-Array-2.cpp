/*
ID: tiankonguse
TASK: A. Suffix Array - 2 A. 后缀数组 - 2
LANG: C++
MAC EOF: ctrl+D
link:
hhttps://codeforces.com/edu/course/2/lesson/2/2/practice/contest/269103/problem/A
PATH: ITMO 学院：试点课程 » 后缀数组 » 步骤2 » 实践
submission: https://codeforces.com/edu/course/2/lesson/2/2/practice/contest/269103/submission/296880365
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

  vector<int> nums2;
  vector<int> rank2;
  vector<int> nums1;
  vector<int> rank1;
  int nn = strlen(str);
  str[nn] = '$';
  nn++;
  n = nn;

  int K = LogN(n);
  bt.resize(K + 1, vector<int>(n, 0));

  nums2.resize(n + 2);  // 计数排序
  rank2.resize(n + 2);  // 计数排序
  rank1.resize(n + 2);  // 计数排序
  nums1.resize(n + 2);  // 计数排序

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
    for (auto& v : nums2) v = 0;
    int maxRightRank = 0;
    for (int j = 0; j < n; j++) {
      int rightRank = LeftRightRank(i, j).second + 1;
      nums2[rightRank]++;
      maxRightRank = max(maxRightRank, rightRank);
    }
    for (int r = 1; r <= maxRightRank; r++) {
      nums2[r] += nums2[r - 1];
    }

    for (auto& v : rank2) v = 0;
    for (int j = 0; j < n; j++) {
      int rightRank = LeftRightRank(i, j).second;
      rank2[nums2[rightRank]] = j;
      nums2[rightRank]++;
    }

    for (auto& v : nums1) v = 0;
    int maxLeftRank = 0;
    for (int r = 0; r < n; r++) {
      int j = rank2[r];
      int leftRank = LeftRightRank(i, j).first + 1;
      nums1[leftRank]++;
      maxLeftRank = max(maxLeftRank, leftRank);
    }
    for (int r = 1; r <= maxLeftRank; r++) {
      nums1[r] += nums1[r - 1];
    }

    for (auto& v : rank1) v = 0;
    for (int r = 0; r < n; r++) {
      int j = rank2[r];
      int leftRank = LeftRightRank(i, j).first;
      rank1[nums1[leftRank]] = j;
      nums1[leftRank]++;
    }

    // 最小的肯定是 $
    auto pre = LeftRightRank(i, rank1[0]);
    int rank = 0;
    for (int r = 0; r < n; r++) {
      int j = rank1[r];
      auto v = LeftRightRank(i, j);
      if (v != pre) {
        pre = v;
        rank++;
      }
      bt[i][j] = rank;
    }

    // printf("i=%d\n", i);
    // for (int j = 0; j < n; j++) {
    //   printf("j=%d rank=%d\n", j, bt[i][j]);
    // }
  }

  for (int j = 0; j < n; j++) {
    nums1[bt[K][j]] = j;
  }
  for (int j = 0; j < n; j++) {
    printf("%d%c", nums1[j], j + 1 == n ? '\n' : ' ');
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