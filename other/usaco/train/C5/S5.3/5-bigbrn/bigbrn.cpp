/*
ID: tiankonguse
TASK: bigbrn
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "bigbrn"
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

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

int n, t;
vector<vector<char>> g;

void Solver() {  //
  scanf("%d%d", &n, &t);
  g.resize(n + 1, vector<char>(n + 1, '1'));
  for (int i = 0; i <= n; i++) {
    g[0][i] = g[i][0] = '0';
  }
  while (t--) {
    int x, y;
    scanf("%d%d", &x, &y);
    g[x][y] = '0';
  }

  vector<int> col(n + 1, 0), row(n + 1, 0), dp(n + 1, 0);

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    row.clear();
    row.resize(n + 1, 0);
    for (int j = 1; j <= n; j++) {
      if (g[i][j] == '0') {
        col[j] = 0;
        row[j] = 0;
      } else {
        col[j] = col[j] + 1;
        row[j] = row[j - 1] + 1;
      }
    }
    for (int j = n; j >= 1; j--) {
      if (g[i][j] == '0') {
        dp[j] = 0;
      } else {
        dp[j] = min(dp[j - 1] + 1, min(col[j], row[j]));
      }
      ans = max(ans, dp[j]);
    }
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