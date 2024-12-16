/*
ID: tiankonguse
TASK: A. Suffix Array - 1 A. 后缀数组 - 1
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/2/1/practice/contest/269100/problem/A
PATH: ITMO 学院：试点课程 » 后缀数组 » 步骤1 » 实践
submission: https://codeforces.com/edu/course/2/lesson/2/1/practice/contest/269100/submission/296870949
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

const int N = 1e5 + 10;
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

vector<pair<ll, int>> nums;
int n;
vector<vector<int>> bt;
void Solver() {  //
  n = strlen(str);
  str[n] = '$';
  n++;

  int K = LogN(n);
  bt.resize(K + 1, vector<int>(n, 0));

  nums.resize(n);
  for (int i = 0; i <= K; i++) {
    for (int j = 0; j < n; j++) {
      ll v = str[j];
      if (i > 0) {
        ll leftRank = bt[i - 1][j];
        ll rightRank = bt[i - 1][(j + (1 << (i - 1))) % n];
        v = leftRank * (n + 1) + rightRank;
      }
      nums[j] = {v, j};
    }
    sort(nums.begin(), nums.end());
    // 最小的肯定是 $
    ll pre = nums.front().first;
    int rank = 1;
    for (int j = 0; j < n; j++) {
      auto [v, inedx] = nums[j];
      if (v != pre) {
        pre = v;
        rank++;
      }
      bt[i][inedx] = rank;
    }

    // printf("i=%d\n", i);
    // for (int j = 0; j < n; j++) {
    //   printf("j=%d rank=%d\n", j, bt[i][j]);
    // }
  }

  for (int j = 0; j < n; j++) {
    nums[j] = {bt[K][j], j};
  }
  sort(nums.begin(), nums.end());
  for (int j = 0; j < n; j++) {
    printf("%d%c", nums[j].second, j + 1 == n ? '\n' : ' ');
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