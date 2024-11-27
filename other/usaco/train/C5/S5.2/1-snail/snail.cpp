/*
ID: tiankonguse
TASK: snail
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "snail"
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

int n;
char g[130][130];
int ans = 1;
int dir4[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
void Update(const int step) {  //
  ans = max(ans, step);
//   if (step == 99) {
//     printf("    --------   \n");
//     for (int i = 0; i <= n + 1; i++) {
//       printf("%s\n", g[i]);
//     }
//     printf("    --------   \n");
//   }
}

void Dfs(const int x, const int y, const int d, const int step) {
  int nowStep = 0;
  int X = x, Y = y;
  do {
    X = X + dir4[d][0];
    Y = Y + dir4[d][1];
    if (g[X][Y] == '0') {
      g[X][Y] = '2';
      nowStep++;
    } else {
      Update(nowStep + step);

      if (g[X][Y] == '1' && nowStep > 0) {  // 撞墙 且有移动，继续尝试
        X = X - dir4[d][0];
        Y = Y - dir4[d][1];
        Dfs(X, Y, (d + 1) % 4, step + nowStep);
        Dfs(X, Y, (d + 3) % 4, step + nowStep);
      }
      break;
    }
  } while (1);

  X = x, Y = y;
  while (nowStep--) {
    X = X + dir4[d][0];
    Y = Y + dir4[d][1];
    g[X][Y] = '0';
  }
}

int Solver(const int x, const int y) {
  if (g[x][y] == 1) {
    return 0;
  }
  for (int d = 0; d < 4; d++) {
    g[x][y] = '2';
    Dfs(x, y, d, 1);
    g[x][y] = '0';
  }
  return ans;
}

void Solver() {  //
  int m;
  scanf("%d%d", &n, &m);
  memset(g, '0', sizeof(g));
  g[0][n + 2] = '\0';
  for (int i = 1; i <= n; i++) {
    g[i][0] = g[0][i] = g[n + 1][i] = g[i][n + 1] = '1';
    g[i][n + 2] = '\0';
  }
  g[n + 1][n + 2] = '\0';
  while (m--) {
    char op[10];
    scanf("%s", op);
    int x = op[0] - 'A' + 1;
    int y = atoi(op + 1);
    g[x][y] = '1';
  }
  printf("%d\n", Solver(1, 1));
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/