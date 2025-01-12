/*
ID: tiankonguse
TASK: T561109 【MX-X7-T2】[LSOT-3] 姬誉蛙
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/T561109?contestId=218816
PATH:
submission: https://github.com/tiankonguse/leetcode-solutions/
*/
#define TASK "A"
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

int n, k;
const ll N = 1e6 + 10;
char str[N];
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  //  freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d%d%s", &n, &k, str);
}

bool Check(const ll mid) {
  // printf("n=%d k=%d mid=%lld\n", n, k, mid);
  int num = 1;
  ll dp[2] = {0, 0};
  for (int i = 0; i < n; i++) {
    int v = str[i] - '0';
    dp[v]++;
    // printf("i=%d num=%d dp[0]=%lld dp[1]=%lld X=%lld\n", i, num, dp[0], dp[1], dp[0] * dp[1]);
    if (dp[0] * dp[1] > mid) {
      num++;
      if (num > k) return false;
      dp[0] = dp[1] = 0;
      dp[v]++;
    }
  }
  // printf("mid true\n");
  return true;
}

ll Search() {
  // Check(3);
  // return 0;
  ll l = 0, r = N * N;
  while (l < r) {
    ll mid = (l + r) / 2;
    if (Check(mid)) {
      // printf("mid=%lld l=%lld r=%lld ok\n", mid, l, r);
      r = mid;
    } else {
      // printf("mid=%lld l=%lld r=%lld err\n", mid, l, r);
      l = mid + 1;
    }
  }
  return r;
}

void Solver() {  //
  printf("%lld\n", Search());
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
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