/*
ID: tiankonguse
TASK: job
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "job"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK);
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

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

int n, ma, mb;
int A[33], B[33];
int t1, t2;

min_queue<pair<int, int>> busyQueA;
min_queue<pair<int, int>> busyQueB;

void Solver() {  //
  scanf("%d%d%d", &n, &ma, &mb);

  for (int i = 0; i < ma; i++) {
    scanf("%d", &A[i]);
    busyQueA.push({A[i], A[i]});  // 时间相同时，选择性能最高的机器
  }
  for (int i = 0; i < mb; i++) {
    scanf("%d", &B[i]);
    busyQueB.push({B[i], B[i]});  // 时间相同时，选择性能最高的机器
  }

  // 对于 A，所有选择是确定的
  vector<int> costA(n, 0);
  for (int i = 0; i < n; i++) {
    auto [t, a] = busyQueA.top();
    busyQueA.pop();
    busyQueA.push({t + a, a});
    costA[i] = t;
  }
  t1 = costA.back();

  vector<int> costB(n, 0);
  for (int i = 0; i < n; i++) {
    auto [t, a] = busyQueB.top();
    busyQueB.pop();
    busyQueB.push({t + a, a});
    costB[i] = t;
  }

  t2 = 0;
  for (int i = 0; i < n; i++) {
    t2 = max(t2, costA[i] + costB[n - 1 - i]);
  }

  printf("%d %d\n", t1, t2);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/