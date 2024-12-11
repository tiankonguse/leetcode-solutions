/*
ID: tiankonguse
TASK: betsy
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "betsy"
#define TASKEX "-wall"

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
unordered_map<ll, ll> HH;
vector<int> row;
vector<int> col;
int flagIndex = 1;

bool Wall(int x, int y) {
  if (row[x] == n && row[x - 1] < n) return true;
  if (col[y] == n && col[y + 1] < n) return true;
  if (y == n && g[x - 1][y] != 1) return false;
  if (x == n && g[x][y + 1] != 1) return false;
  if (x == 1 && g[x][y - 1] != 1) return false;
  if (y == 1 && g[x - 1][y] != 1) return false;

  return false;
}
bool Connect(int num) {
  flagIndex++;
  int x = n, y = 1;
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
      if (g[X][Y] == 1 || g[X][Y] == flagIndex) continue;

      g[X][Y] = flagIndex;
      que.push({X, Y});
      num++;
    }
  }
  return num == n * n;
}

inline void Set(int x, int y) {
  g[x][y] = 1;
  row[x]++;
  col[y]++;
}
inline void UnSet(int x, int y) {
  g[x][y] = 0;
  row[x]--;
  col[y]--;
}
ll Dfs(const int x, const int y, const ll h, const int num) {
  // if (n == 6) return 1770;
  // if (n == 7) return 88418;
  const ll hh = h | (1LL << ((x - 1) * n + (y - 1)));
  if (H[x][y].count(hh)) return H[x][y][hh];
  if (HH.count(hh)) return 0;  // 死胡同
  ll& ret = H[x][y][hh];
  ret = 0;
  if (x == n && y == 1) {
    if (num == n * n) {
      return ret = 1;
    } else {
      return ret = 0;
    }
  }

  if (Wall(x, y) || !Connect(num)) {
    HH[hh] = 0;
    return ret = 0;
  }

  for (int i = 0; i < 4; i++) {
    int X = x + dir4[i][0];
    int Y = y + dir4[i][1];
    if (g[X][Y] == 1) continue;

    Set(X, Y);
    ret += Dfs(X, Y, hh, num + 1);
    UnSet(X, Y);
  }
  //   printf("x=%d y=%d num=%d ret=%lld\n", x, y, num, ret);
  return ret;
}

void Solver() {  //
  scanf("%d", &n);
  memset(g, 0, sizeof(g));
  H.resize(n + 1, vector<unordered_map<ll, ll>>(n + 1));

  for (int i = 0; i <= n + 1; i++) {
    g[i][0] = g[0][i] = g[n + 1][i] = g[i][n + 1] = 1;
  }
  row.resize(n + 1, 0);
  col.resize(n + 1, 0);
  row[0] = row[n] = col[0] = col[n] = n;
  Set(1, 1);
  printf("%lld\n", Dfs(1, 1, 0, 1));
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
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*
5
86
my 用时: 617ms

6
1770
my 用时: 897ms

7
88418
my 用时: 15985ms - prune horizontal/vertical walls
my 用时: 15649ms - prune block-offs 优化
*/