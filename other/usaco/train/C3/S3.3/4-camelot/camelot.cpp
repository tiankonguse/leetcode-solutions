/*
ID: tiankonguse
TASK: camelot
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "camelot"

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

int n, m;

int dis[33][33][33][33];

int dir[8][2] = {{-1, -2}, {-1, 2}, {-2, 1}, {-2, -1},
                 {1, 2},   {1, -2}, {2, 1},  {2, -1}};
void Bfs(int sx, int sy) {
  auto g = dis[sx][sy];

  queue<pair<int, int>> que;
  que.push({sx, sy});
  g[sx][sy] = 0;

  while (!que.empty()) {
    auto [x, y] = que.front();
    que.pop();
    const int cost = g[x][y];

    for (int i = 0; i < 8; i++) {
      int X = x + dir[i][0];
      int Y = y + dir[i][1];
      if (X < 0 || X >= n || Y < 0 || Y >= m) continue;
      if (g[X][Y] != -1) continue;

      g[X][Y] = cost + 1;
      que.push({X, Y});
    }
  }
}

void Init() {
  memset(dis, -1, sizeof(dis));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      Bfs(i, j);
    }
  }
}

char row[2];
int col;

pair<int, int> Trans() {
  int x = row[0] - 'A';
  int y = col - 1;
  return {x, y};
}

vector<pair<int, int>> knights;
int path[33][33];
pair<bool, int> Solver(int sx, int sy, int kx, int ky) {
  memset(path, -1, sizeof(path));
  int kingCost = max(abs(sx - kx), abs(sy - ky));

  path[sx][sy] = 0;
  auto BfsPath = [sx, sy, kx, ky, &kingCost](int x, int y) {
    queue<pair<int, int>> que;
    que.push({x, y});
    path[x][y] = dis[sx][sy][x][y];
    while (!que.empty()) {
      auto [x, y] = que.front();
      que.pop();
      kingCost = min(kingCost, max(abs(kx - x), abs(ky - y)));
      for (int i = 0; i < 8; i++) {
        int X = x + dir[i][0];
        int Y = y + dir[i][1];
        if (X < 0 || X >= n || Y < 0 || Y >= m) continue;
        if (dis[X][Y][sx][sy] == -1) continue;
        if (path[X][Y] != -1) continue;
        if (dis[X][Y][sx][sy] + 1 == path[x][y]) {
          path[X][Y] = dis[X][Y][sx][sy];
          que.push({X, Y});
        }
      }
    }
  };

  int ans = 0;
  for (auto [x, y] : knights) {
    if (dis[sx][sy][x][y] == -1) {
      return {false, -1};
    }
    BfsPath(x, y);
    ans += dis[sx][sy][x][y];
  }
  ans += kingCost;
  return {true, ans};
}

int Solver(int kx, int ky) {
  int k = knights.size();
  if (k == 0) {
    return 0;
  }
  int ans = INT_MAX;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      auto [ok, cost] = Solver(i, j, kx, ky);
      if (ok) {
        ans = min(ans, cost);
      }
    }
  }
  return ans;
}

void Solver() {  //
  scanf("%d%d", &m, &n);
  Init();

  scanf("%s%d", row, &col);

  auto [kx, ky] = Trans();
  while (~scanf("%s%d", row, &col)) {
    knights.push_back(Trans());
  }

  printf("%d\n", Solver(kx, ky));
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/