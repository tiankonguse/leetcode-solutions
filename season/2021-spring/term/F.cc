#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

const int inf = 0x3f3f3f3f;
const int maxn = 2000000;

struct Dinic {
  int n;  // n个顶点
  struct edge {
    int from, to, cap;
  };
  vector<int> G[maxn];
  vector<edge> e;
  int level[maxn], iter[maxn];

  void init() {
    for (int i = 0; i <= n; i++) G[i].clear();
    e.clear();
  }

  void add_edge(int u, int v, int cap) {
    e.push_back((edge){u, v, cap});
    e.push_back((edge){v, u, 0});
    int m = e.size();
    G[u].push_back(m - 2);
    G[v].push_back(m - 1);
  }

  void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      for (int i = 0; i < G[u].size(); i++) {
        edge& te = e[G[u][i]];
        if (te.cap > 0 && level[te.to] < 0) {
          level[te.to] = level[u] + 1;
          que.push(te.to);
        }
      }
    }
  }

  int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int& i = iter[v]; i < G[v].size(); i++) {
      edge& tpe = e[G[v][i]];
      if (tpe.cap > 0 && level[v] < level[tpe.to]) {
        int d = dfs(tpe.to, t, min(f, tpe.cap));
        if (d > 0) {
          tpe.cap -= d;
          e[G[v][i] ^ 1].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  int max_flow(int s, int t) {
    int flow = 0;
    for (;;) {
      bfs(s);
      if (level[t] < 0) return flow;
      memset(iter, 0, sizeof(iter));
      int f;
      while ((f = dfs(s, t, 0x3fffffff)) > 0) flow += f;
    }
  }
} di1;
int N, S, T, P;

int idx[2][10010];
int vinuse = 0;
vector<pair<int, int>> st, jp;

int nextx[4] = {0, 0, -1, 1};
int nexty[4] = {1, -1, 0, 0};

bool isGood(vector<string>& grid) {
  int len = grid[0].size();
  bool hasJP = false;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == 'C') {
        for (int k = 0; k < 4; k++) {
          int ii = i + nextx[k];
          int jj = j + nexty[k];
          if (ii < 0 || jj < 0 || ii >= 2 || jj >= len) continue;
          // printf("%c\n", grid[ii][jj]);
          if (grid[ii][jj] == 'S') return false;
          if (grid[ii][jj] == 'P') hasJP = true;
        }
      }
    }
  }
  // puts("@@@@@");
  if (!hasJP) return true;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == 'P') {
        for (int k = 0; k < 4; k++) {
          int ii = i + nextx[k];
          int jj = j + nexty[k];
          if (ii < 0 || jj < 0 || ii >= 2 || jj >= len) continue;
          if (grid[ii][jj] == 'S') return false;
        }
      }
    }
  }
  return true;
}

bool STOJP = false;
void kay(vector<string>& grid) {
  STOJP = false;
  int len = grid[0].size();
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == 'S') {
        for (int k = 0; k < 4; k++) {
          int ii = i + nextx[k];
          int jj = j + nexty[k];
          if (ii < 0 || jj < 0 || ii >= 2 || jj >= len) continue;
          if (grid[ii][jj] == 'P') {
            STOJP = true;
            return;
          }
        }
      }
    }
  }
}

class Solution {
 public:
  int guardCastle(vector<string>& grid) {
    if (!isGood(grid)) return -1;
    kay(grid);
    int len = grid[0].size();
    memset(idx, -1, sizeof idx);
    st.clear();
    jp.clear();
    vinuse = 0;
    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid[i].size(); j++) {
        if (grid[i][j] == '.') {
          idx[i][j] = ++vinuse;
        }
        if (grid[i][j] == '#') {
          continue;
        }
        if (grid[i][j] == 'S') {
          st.push_back({i, j});
        }
        if (grid[i][j] == 'P') {
          jp.push_back({i, j});
        }
        if (grid[i][j] == 'C') {
          T = idx[i][j] = ++vinuse;
        }
      }
    }
    S = ++vinuse;
    P = ++vinuse;
    N = vinuse;
    /*
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < len; j++) {
            printf("%d ", idx[i][j]);
        }
        puts("");
    }
    printf("S = %d, P = %d, T = %d\n", S, P, T);
    */
    di1.n = 2 * N;
    di1.init();

    for (int i = 1; i <= N; i++) {
      int val = 1;
      if (i == S || i == P || i == T) val = inf;
      di1.add_edge(2 * i - 1, 2 * i, val);
    }

    for (int i = 0; i < st.size(); i++) {
      int x = st[i].first, y = st[i].second;
      for (int j = 0; j < 4; j++) {
        int xx = x + nextx[j];
        int yy = y + nexty[j];
        if (xx < 0 || yy < 0 || xx >= 2 || yy >= len) continue;
        if (idx[xx][yy] == -1) continue;
        int idfrom = S;
        int idto = idx[xx][yy];
        di1.add_edge(2 * idfrom, 2 * idto - 1, inf);
        di1.add_edge(2 * idto, 2 * idfrom - 1, inf);
      }
    }

    for (int i = 0; i < jp.size(); i++) {
      int x = jp[i].first, y = jp[i].second;
      for (int j = 0; j < 4; j++) {
        int xx = x + nextx[j];
        int yy = y + nexty[j];
        if (xx < 0 || yy < 0 || xx >= 2 || yy >= len) continue;
        if (idx[xx][yy] == -1) continue;
        int idfrom = P;
        int idto = idx[xx][yy];
        di1.add_edge(2 * idfrom, 2 * idto - 1, inf);
        di1.add_edge(2 * idto, 2 * idfrom - 1, inf);

        if (STOJP) {
          int idfrom = S;
          int idto = idx[xx][yy];
          di1.add_edge(2 * idfrom, 2 * idto - 1, inf);
          di1.add_edge(2 * idto, 2 * idfrom - 1, inf);
        }
      }
    }

    for (int x = 0; x < 2; x++) {
      for (int y = 0; y < len; y++) {
        if (idx[x][y] == -1) continue;
        if (idx[x][y] == T) continue;
        for (int j = 0; j < 4; j++) {
          int xx = x + nextx[j];
          int yy = y + nexty[j];
          if (xx < 0 || yy < 0 || xx >= 2 || yy >= len) continue;
          if (idx[xx][yy] == -1) continue;
          int idfrom = idx[x][y];
          int idto = idx[xx][yy];
          di1.add_edge(2 * idfrom, 2 * idto - 1, inf);
          di1.add_edge(2 * idto, 2 * idfrom - 1, inf);
        }
      }
    }
    int f = di1.max_flow(2 * S, 2 * T - 1);
    return f;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
