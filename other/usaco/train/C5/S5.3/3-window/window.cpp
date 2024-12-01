/*
ID: tiankonguse
TASK: window
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "window"
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

char line[100];

int bottom = 0;
int top = 0;

vector<tuple<char, ll, ll, ll, ll>> nums;
map<int, int> h;                        // hIndex->numsInedx
unordered_map<char, pair<int, int>> H;  // p->{numsInedx, hIndex}

vector<int> dotX, dotY;
unordered_map<ll, int> hx, hy;

pair<ll, ll> Solver(char p) {
  auto [numsInedx, hIndex] = H[p];
  const auto [_, x0, y0, X0, Y0] = nums[numsInedx];
  const ll all = (X0 - x0) * (Y0 - y0);
  dotX.clear();
  dotY.clear();
  dotX.reserve(H.size() * 2);
  dotY.reserve(H.size() * 2);
  auto Merge =
      [p0 = nums[numsInedx]](
          tuple<char, ll, ll, ll, ll> p1) -> tuple<char, ll, ll, ll, ll> {
    auto [p, x0, y0, X0, Y0] = p0;
    auto [_, x1, y1, X1, Y1] = p1;
    return {_, max(x1, x0), max(y1, y0), min(X1, X0), min(Y1, Y0)};
  };

  for (auto it = ++h.find(hIndex); it != h.end(); it++) {  //
    auto [_, x1, y1, X1, Y1] = Merge(nums[it->second]);
    if (x1 >= X1 || y1 >= Y1) continue;  // 没有交集
    dotX.push_back(x1);
    dotX.push_back(X1);
    dotY.push_back(y1);
    dotY.push_back(Y1);
  }
  if (dotX.size() == 0) {
    return {all, all};
  }
  dotX.push_back(x0);
  dotX.push_back(X0);
  dotY.push_back(y0);
  dotY.push_back(Y0);
  sort(dotX.begin(), dotX.end());
  sort(dotY.begin(), dotY.end());
  dotX.erase(unique(dotX.begin(), dotX.end()), dotX.end());
  dotY.erase(unique(dotY.begin(), dotY.end()), dotY.end());

  int xn = dotX.size();
  int yn = dotY.size();
  hx.clear();
  hy.clear();
  for (int i = 0; i < xn; i++) {
    hx[dotX[i]] = i;
  }
  for (int i = 0; i < yn; i++) {
    hy[dotY[i]] = i;
  }
  vector<vector<int>> g(xn, vector<int>(yn, 1));           // 先暴力计算
  for (auto it = ++h.find(hIndex); it != h.end(); it++) {  //
    auto [_, x1, y1, X1, Y1] = Merge(nums[it->second]);
    if (x1 >= X1 || y1 >= Y1) continue;  // 没有交集
    int xl = hx[x1], xr = hx[X1];
    int yl = hy[y1], yr = hy[Y1];
    for (int x = xl; x < xr; x++) {
      for (int y = yl; y < yr; y++) {
        g[x][y] = 0;
      }
    }
  }

  ll visible = 0;
  int xl = hx[x0], xr = hx[X0];
  int yl = hy[y0], yr = hy[Y0];
  for (int x = xl; x < xr; x++) {
    for (int y = yl; y < yr; y++) {
      if (g[x][y] == 0) continue;
      visible += (dotX[x + 1] - dotX[x]) * (dotY[y + 1] - dotY[y]);
    }
  }
  return {visible, all};
}

void Solver() {  //
  while (~scanf("%s", line)) {
    char c = line[0];
    char p = line[2];
    if (c == 'w') {
      int x, y, X, Y;
      sscanf(line, "w(%c,%d,%d,%d,%d)", &p, &x, &y, &X, &Y);
      nums.push_back({p, min(x, X), min(y, Y), max(x, X), max(y, Y)});
      top++;
      int numsInedx = nums.size() - 1;
      int hIndex = top;
      H[p] = {numsInedx, hIndex};
      h[hIndex] = numsInedx;

    } else if (c == 't') {
      auto& [numsInedx, hIndex] = H[p];
      h.erase(hIndex);
      top++;
      hIndex = top;
      h[hIndex] = numsInedx;
    } else if (c == 'b') {
      auto& [numsInedx, hIndex] = H[p];
      h.erase(hIndex);
      bottom--;
      hIndex = bottom;
      h[hIndex] = numsInedx;
    } else if (c == 'd') {
      auto& [numsInedx, hIndex] = H[p];
      h.erase(hIndex);
      H.erase(p);
    } else {
      auto [visible, all] = Solver(p);
      printf("%.3f\n", visible * 100.0 / all);
    }
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