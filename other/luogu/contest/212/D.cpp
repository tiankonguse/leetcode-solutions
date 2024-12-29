/*
ID: tiankonguse
TASK: D
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "D"
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

int m;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d", &m);
}

const int N = 5100;
vector<vector<int>> g;
vector<int> flag;
int n = 1;
void Insert(int X, int L, int K) {
  for (int k = 0; k < K; k++) {
    int pre = X;
    for (int l = 0; l < L; l++) {
      int now = ++n;
      g[pre].push_back(now);
      pre = now;
    }
  }
}
void Delete(int X) { flag[X] = 1; }

vector<ll> nums;
ll ans = 0;
void Dfs(int x, int dep) {
  if (flag[x]) return;
  nums[dep]++;
  ans = max(ans, nums[dep]);
  for (auto y : g[x]) {
    Dfs(y, dep + 1);
  }
}
ll Search() {
  nums.clear();
  nums.resize(N, 0);
  ans = 0;
  Dfs(1, 1);
  return ans;
};

void Solver() {  //
  g.resize(N);
  flag.resize(N);
  int op;
  while (m--) {
    scanf("%d", &op);
    if (op == 1) {
      ll x, l, k;
      scanf("%lld%lld%lld", &x, &l, &k);
      Insert(x, l, k);
    } else if (op == 2) {
      ll x;
      scanf("%lld", &x);
      Delete(x);
    } else {
      printf("%lld\n", Search());
    }
  }
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