/*
ID: tiankonguse
TASK: frameup
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "frameup"
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

int n, m;
char str[33][33];
vector<vector<int>> g;
vector<vector<int>> trbl;
enum DIR { T = 0, R = 1, B = 2, L = 3 };
vector<int> degree;
vector<int> flag;

void Input() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", str[i]);
  }
}

vector<int> dotExist;
void InitBound() {
  dotExist.resize(26, 0);
  trbl.resize(26, vector<int>({n, -1, -1, m}));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char c = str[i][j];
      if (c == '.') continue;
      int v = c - 'A';
      dotExist[v] = 1;
      trbl[v][T] = min(trbl[v][T], i);
      trbl[v][R] = max(trbl[v][R], j);
      trbl[v][B] = max(trbl[v][B], i);
      trbl[v][L] = min(trbl[v][L], j);
    }
  }
}

void BuildGraph() {
  g.resize(26, vector<int>(26, 0));
  auto BindUV = [](char c, int u) {
    if (c == '.') return;
    g[u][c - 'A'] = 1;
  };

  for (int v = 0; v < 26; v++) {
    if (!dotExist[v]) continue;  // 不存在
    const int t = trbl[v][T];
    const int b = trbl[v][B];
    const int l = trbl[v][L];
    const int r = trbl[v][R];
    for (int i = t; i <= b; i++) {
      BindUV(str[i][l], v);
      BindUV(str[i][r], v);
    }
    for (int i = l; i <= r; i++) {
      BindUV(str[t][i], v);
      BindUV(str[b][i], v);
    }
  }
}

int dotNum = 0;
void InitDegree() {
  degree.resize(26, 0);
  for (int i = 0; i < 26; i++) {
    if (g[i][i]) dotNum++;
    for (int j = 0; j < 26; j++) {
      if (i == j) continue;
      degree[j] += g[i][j];
    }
  }
}

vector<string> ans;
string buf;

void Dfs() {
  if (int(buf.size()) == dotNum) {
    ans.push_back(buf);
    return;
  }
  for (int i = 0; i < 26; i++) {
    if (!dotExist[i]) continue;  // 点不存在
    if (degree[i]) continue;     // 入度不为 0
    if (flag[i]) continue;       // 已经处理过了
    flag[i] = 1;
    buf.push_back('A' + i);
    for (int j = 0; j < 26; j++) {
      if (i == j) continue;
      if (g[i][j]) {
        degree[j]--;
      }
    }

    Dfs();

    for (int j = 0; j < 26; j++) {
      if (i == j) continue;
      if (g[i][j]) {
        degree[j]++;
      }
    }
    buf.pop_back();
    flag[i] = 0;
  }
}

void Solver() {  //
  Input();
  InitBound();
  BuildGraph();
  InitDegree();
  flag.resize(26, 0);
  Dfs();
//   printf("ansNum=%d\n", int(ans.size()));
  sort(ans.begin(), ans.end());
  for (auto& s : ans) {
    printf("%s\n", s.data());
  }
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/