/*
ID: tiankonguse
TASK: fence9
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "fence9"

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

int Solver(int X, int Y) {
  ll ans = 0;
  for (int x = 1; x < X; x++) {
    int y = (Y * x + X - 1) / X;  // 向上取整
    ans += max(y - 1, 0);
  }
  return ans;
}

int Line(int X, int Y) {
  ll ans = 0;
  for (int x = 1; x < X; x++) {
    if (Y * x % X == 0) {
      ans++;
    }
  }
  return ans;
}

void Solver() {  //
  int n, m, p;
  int ans = 0;
  scanf("%d%d%d", &n, &m, &p);

  if (n == 0) {  // 右半部
    ans = Solver(p, m);
  } else if (n == p) {  // 只有左半部
    ans = Solver(n, m);
  } else if (n < p) {  // 左半部 + 右半部 + 分割线
    ans = Solver(n, m) + Solver(p - n, m) + m - 1;
  } else {
    ans = Solver(n, m) - Solver(n - p, m) - Line(n - p, m);
  }
  printf("%d\n", ans);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/