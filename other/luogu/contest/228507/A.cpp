/*
ID: tiankonguse
TASK: T454128 「TPOI-1A」鞋子特大号
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
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
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 1000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int t;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  // freopen(TASK ".in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d", &t);
}
const int N = 1000010;
const int M = 88499;
bool is[N];
int prm[M];
int firstFac[N];
int getprm() {
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  memset(is, 1, sizeof(is));
  memset(firstFac, 0, sizeof(firstFac));
  prm[k++] = 2;
  is[0] = is[1] = 0;
  for (i = 4; i < N; i += 2) {
    if (firstFac[i] == 0) firstFac[i] = 2;
    is[i] = 0;
  }
  for (i = 3; i < e; i += 2) {
    if (is[i]) {
      prm[k++] = i;
      for (int s = i + i, j = i * i; j < N; j += s) {
        if (firstFac[j] == 0) firstFac[j] = i;
        is[j] = 0;
      }
    }
  }
  for (; i < N; i += 2)
    if (is[i]) prm[k++] = i;
  // printf("k=%d\n", k);
  return k;
}

vector<int> ans;
void InitPrime() {  //
  getprm();
  ans.resize(N, 0);
  for (int i = 1; i < N; i++) {
    if (firstFac[i] != 0) {
      ans[i] = ans[i / firstFac[i]] + 1;
    }
  }
}

void Solver() {  //
  InitPrime();
  ll op, x;
  while (t--) {
    scanf("%lld%lld", &op, &x);
    if (op == 1) {
      printf("%d\n", ans[x]);
    } else {
      printf("%llu\n", 2llu << x);
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