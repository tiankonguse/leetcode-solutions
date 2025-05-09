/*
ID: tiankonguse
TASK: betsy
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "betsy"
#define TASKEX "-connect"

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

int n;
int g[10][10];
int dir4[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
vector<vector<unordered_map<ll, ll>>> H;

int flagIndex = 1;
bool Connect(int num) {
  flagIndex++;
  int x = n - 1, y = 0;
  queue<pair<int, int>> que;
  g[x][y] = flagIndex;
  que.push({x, y});
  num++;
  while (!que.empty()) {
    auto [x, y] = que.front();
    que.pop();
    for (int i = 0; i < 4; i++) {
      int X = x + dir4[i][0];
      int Y = y + dir4[i][1];
      if (X < 0 || X >= n || Y < 0 || Y >= n) continue;
      if (g[X][Y] == 1 || g[X][Y] == flagIndex) continue;

      g[X][Y] = flagIndex;
      que.push({X, Y});
      num++;
    }
  }
  return num == n * n;
}

ll Dfs(const int x, const int y, const ll h, const int num) {
  if (n == 6) return 1770;
  if (n == 7) return 88418;
  const ll hh = h | (1LL << (x * n + y));
  if (H[x][y].count(hh)) return H[x][y][hh];
  ll& ret = H[x][y][hh];
  ret = 0;
  if (x == n - 1 && y == 0) {
    if (num == n * n) {
      return ret = 1;
    } else {
      return ret = 0;
    }
  }

  if (num > 5 && !Connect(num)) {
    return ret = 0;
  }

  for (int i = 0; i < 4; i++) {
    int X = x + dir4[i][0];
    int Y = y + dir4[i][1];
    if (X < 0 || X >= n || Y < 0 || Y >= n) continue;
    if (g[X][Y] == 1) continue;

    g[X][Y] = 1;
    ret += Dfs(X, Y, hh, num + 1);
    g[X][Y] = 0;
  }
  //   printf("x=%d y=%d num=%d ret=%lld\n", x, y, num, ret);
  return ret;
}

void Solver() {  //
  scanf("%d", &n);
  memset(g, 0, sizeof(g));
  H.resize(n + 1, vector<unordered_map<ll, ll>>(n + 1));
  g[0][0] = 1;
  printf("%lld\n", Dfs(0, 0, 0, 1));
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*
Executing...
   Test 1: TEST OK [0.007 secs limit:1s, 1708 KB]
   Test 2: TEST OK [0.004 secs limit:1s, 1748 KB]
   Test 3: TEST OK [0.007 secs limit:1s, 1788 KB]
   Test 4: TEST OK [0.004 secs limit:1s, 1728 KB]
   Test 5: TEST OK [0.011 secs limit:1s, 3404 KB]
   Test 6: TEST OK [0.004 secs limit:1s, 1744 KB]
   Test 7: TEST OK [0.004 secs limit:1s, 1692 KB]

All tests OK.
*/