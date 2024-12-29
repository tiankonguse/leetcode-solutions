/*
ID: tiankonguse
TASK: B
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "B"
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

// 朴素并查集
// 参考资料：https://oi-wiki.org/ds/dsu/
// 树上并查集每个子树需要维护一个集合，保证大集合向小集合合并，并引用返回大集合就不会超时了

class Dsu {
  vector<int> fa;

 public:
  void Init(int n) {
    fa.resize(n);
    for (int i = 0; i < n; i++) {
      fa[i] = i;
    }
  }

  int Find(int x) {
    if (fa[x] != x) {
      fa[x] = Find(fa[x]);
    }
    return fa[x];
  }

  // Union，也成为了 Merge
  void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x != y) {
      if (x < y) {
        fa[y] = x;
      } else {
        fa[x] = y;
      }
    }
  }
};
int n, m;
vector<pair<int, int>> coverPaths;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  coverPaths.resize(m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &coverPaths[i].first, &coverPaths[i].second);
  }
}

vector<vector<pair<int, int>>> g;
vector<pair<int, int>> ans;
Dsu dsu;
int edgeIndex = 0;

void Add(int x, int y) {
  edgeIndex++;
  g[x].push_back({y, edgeIndex});
  g[y].push_back({x, edgeIndex});
}

bool TrySolver() {
  g.resize(n + 1);
  dsu.Init(n + 1);
  for (const auto& [x, y] : coverPaths) {
    const int X = dsu.Find(x);
    const int Y = dsu.Find(y);
    if (X == Y) {
      return false;
    }
    dsu.Union(X, Y);
    Add(x, y);
  }
  vector<int> delEdges(2 * n + 10, 0);
  vector<int> aloneDots;
  aloneDots.reserve(n + 1);

  int root = -1;  // m 至少为 1， 故肯定存在根
  for (int i = 1; i <= n; i++) {
    if (g[i].empty()) {
      aloneDots.push_back(i);
      continue;  // 没有出现的点
    }
    if (root == -1) {
      root = i;
      continue;  // 出现的最小值当做根
    }
    int X = dsu.Find(i);
    if (X == root) {
      continue;  // 已经与根相连
    }

    // 新的联通分支
    auto [Y, YI] = g[X].back();  // 随便一个联通的点
    delEdges[YI] = 1;            // 删除边 [X,Y]
    dsu.Union(X, root);          // 新增边 [root, X]
    Add(root, X);
    dsu.Union(Y, root);  // 新增边 [root, Y]
    Add(root, Y);
  }

  if (!aloneDots.empty()) {
    for (int i = 1; i < int(aloneDots.size()); i++) {  // 独立点收尾相连
      int X = aloneDots[i - 1];
      int Y = aloneDots[i];
      Add(X, Y);
    }

    int l = aloneDots.front();
    int r = aloneDots.back();

    int X = root;
    auto [Y, YI] = g[X].back();  // 随便一个联通的点
    delEdges[YI] = 1;            // 删除边 [X,Y]
    Add(X, l);                   // 新增边 [X, l]
    Add(r, Y);                   // 新增边 [r, Y]
  }
  ans.reserve(n);
  for (int x = 1; x <= n; x++) {
    for (auto [y, yi] : g[x]) {
      if (delEdges[yi]) continue;
      if (x < y) {
        ans.push_back({x, y});
      }
    }
  }
  return true;
}

void Solver() {  //
  if (!TrySolver()) {
    printf("No\n");
  } else {
    printf("Yes\n");
    for (auto [x, y] : ans) {
      printf("%d %d\n", x, y);
    }
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
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

*/