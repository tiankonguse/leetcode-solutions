/*
ID: tiankonguse
TASK: tour
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "tour"
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

vector<vector<int>> g;
vector<vector<int>> dp;
unordered_map<string, int> H;
char name1[22];
char name2[22];
int n, v;

int Dfs(int a, int b) {  // 边的个数
  int& ret = dp[a][b];
  if (ret != INT_MAX) return ret;
  ret = INT_MIN;  // 没答案
  if (a == n - 1 || b == n - 1) {
    if (g[a][b]) {
      ret = max(ret, 1);
    }
    return ret;
  }
  for (int c = max(a, b) + 1; c < n; c++) {
    if (g[a][c]) {  // 出发时， a->c->...->b
      ret = max(ret, Dfs(c, b) + 1);
    }

    if (g[b][c]) {  // 返航时， a->...->c->b
      ret = max(ret, Dfs(a, c) + 1);
    }
  }
  //   printf("%d->...->%d cost=%d\n", a, b, ret);
  return ret;
}

int SolverEx() {
  if (n == 2 && g[0][1]) {
    return 2;
  }
  int ans = 1;
  for (int i = 1; i < n; i++) {
    if (g[0][i]) {
      ans = max(ans, 1 + Dfs(0, i));
    }
  }
  return ans;
}

void Solver() {  //
  scanf("%d%d", &n, &v);
  g.resize(n, vector<int>(n, 0));
  dp.resize(n, vector<int>(n, INT_MAX));
  for (int i = 0; i < n; i++) {
    scanf("%s", name1);
    H[name1] = i;
  }
  while (v--) {
    scanf("%s%s", name1, name2);
    int a = H[name1];
    int b = H[name2];
    g[a][b] = g[b][a] = 1;
  }
  printf("%d\n", SolverEx());
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*
8 9
Vancouver
Yellowknife
Edmonton
Calgary
Winnipeg
Toronto
Montreal
Halifax
Vancouver Edmonton
Vancouver Calgary
Calgary Winnipeg
Winnipeg Toronto
Toronto Halifax
Montreal Halifax
Edmonton Montreal
Edmonton Yellowknife
Edmonton Calgary

=>7

5 5
C1
C2
C3
C4
C5
C5 C4
C2 C3
C3 C1
C4 C1
C5 C2
=>1

8 12
A
B
C
D
E
F
G
H
A B
A C
C B
D C
D B
D E
D F
E F
E G
D H
H F
H G
=>1
*/