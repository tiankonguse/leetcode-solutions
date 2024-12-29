/*
ID: tiankonguse
TASK: D
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "D-V2"
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

const int N = 501000;
vector<int> deps;
vector<vector<int>> g;
vector<int> delFlag;
vector<ll> nums;
int n = 1;

set<pair<ll, ll>> h;

void AddDep(int d) {  //
  int oldNum = nums[d];
  if (oldNum > 0) {
    h.erase({oldNum, d});
  }

  nums[d]++;
  int newNum = nums[d];
  h.insert({newNum, d});
}
void DelDep(int d) {  //
  int oldNum = nums[d];
  h.erase({oldNum, d});

  nums[d]--;
  int newNum = nums[d];
  if (newNum > 0) {
    h.insert({newNum, d});
  }
}
void InitDep() {
  deps[1] = 1;
  AddDep(1);
}
ll GetMaxDep() {  //
  return h.rbegin()->first;
}

void Insert(int X, int L, int K) {
  for (int k = 0; k < K; k++) {
    int pre = X;
    for (int l = 0; l < L; l++) {
      int now = ++n;
      deps[now] = deps[pre] + 1;
      AddDep(deps[now]);
      g[pre].push_back(now);
      pre = now;
    }
  }
}
void DfsDel(int X) {
  if (delFlag[X]) return;
  delFlag[X] = 1;
  DelDep(deps[X]);
  for (auto Y : g[X]) {
    DfsDel(Y);
  }
}

void Delete(int X) { DfsDel(X); }

ll Search() { return GetMaxDep(); };

void Solver() {  //
  g.resize(N);
  delFlag.resize(N);
  deps.resize(N);
  nums.resize(N, 0);
  InitDep();
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