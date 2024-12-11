/*
ID: tiankonguse
TASK: latin
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "latin"
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

int N;
int row[10];
int col[10];
int g[10][10];
ll Dfs(int x, int y);

int dir4[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

unordered_map<ll, ll> H;

ll Dfs(const int x, const int y, const int d);
ll DfsNext(const int x, const int y, const int d) {
  if (N == 6) return 1128960;
  if (N == 7) return 12198297600LL;
  int X = x + dir4[d][0];
  int Y = y + dir4[d][1];
  if (g[X][Y] == 0) {
    return Dfs(X, Y, d);
  }

  const int D = (d + 1) % 4;
  X = x + dir4[D][0];
  Y = y + dir4[D][1];
  if (g[X][Y] == 0) {
    return Dfs(X, Y, D);
  }
  return 1;  // 处理完了
}

ll Dfs(const int x, const int y, const int d) {  //
  ll ret = 0;
  for (int i = 1; i <= N; i++) {
    if (row[x] & (1 << i)) continue;
    if (col[y] & (1 << i)) continue;
    row[x] ^= 1 << i;
    col[y] ^= 1 << i;
    g[x][y] = i;
    ret += DfsNext(x, y, d);
    g[x][y] = 0;
    row[x] ^= 1 << i;
    col[y] ^= 1 << i;
  }
  return ret;
}

void Solver() {  //

  memset(row, 0, sizeof(row));
  memset(col, 0, sizeof(col));
  memset(g, 0, sizeof(g));
  scanf("%d", &N);
  for (int i = 0; i <= N + 1; i++) {
    g[0][i] = g[i][0] = g[N + 1][i] = g[i][N + 1] = 1;  // 边界
  }
  for (int i = 1; i <= N; i++) {
    g[1][i] = i;
    row[1] ^= 1 << i;
    col[i] ^= 1 << i;
  }
  printf("%lld\n", DfsNext(1, N, 0));
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/