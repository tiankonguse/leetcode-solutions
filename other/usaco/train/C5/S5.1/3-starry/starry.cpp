/*
ID: tiankonguse
TASK: starry
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "starry"
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

const char S = '1';
const char T = '2';
const int N = 111;
int n, m;
char str[N][N];
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
vector<pair<int, int>> stars;
queue<pair<int, int>> que;
unordered_map<ll, char> H;
int ansNum = 0;

void Solver(int x, int y) {  //
  int l = N, r = -1, t = N, b = -1;

  stars.reserve(200);
  stars.clear();

  auto Add = [&l, &r, &b, &t](int x, int y) {
    str[x][y] = T;
    stars.push_back({x, y});
    que.push({x, y});
    l = min(l, y);
    r = max(r, y);
    t = min(t, x);
    b = max(b, x);
  };

  Add(x, y);

  while (!que.empty()) {
    auto [x, y] = que.front();
    que.pop();
    for (int i = 0; i < 8; i++) {
      int X = x + dir8[i][0];
      int Y = y + dir8[i][1];
      if (X < 0 || X >= n || Y < 0 || Y >= m) continue;
      if (str[X][Y] != S) continue;
      Add(X, Y);
    }
  }

  auto Matrixhash = [](int t, int b, int tb, int l, int r, int lr) {
    ll h = 0;
    for (int i = t; i != (b + tb); i += tb) {
      for (int j = l; j != (r + lr); j += lr) {
        if (str[i][j] == T) {
          h = (h * 2 + 1) % mod;
        } else {
          h = (h * 2) % mod;
        }
      }
    }
    return h;
  };
  auto Matrixhash2 = [](int t, int b, int tb, int l, int r, int lr) {
    ll h = 0;
    for (int j = l; j != (r + lr); j += lr) {
      for (int i = t; i != (b + tb); i += tb) {
        if (str[i][j] == T) {
          h = (h * 2 + 1) % mod;
        } else {
          h = (h * 2) % mod;
        }
      }
    }
    return h;
  };

  vector<ll> hs;
  hs.push_back(Matrixhash(t, b, 1, l, r, 1));  // 上->下 & 左->右
  hs.push_back(Matrixhash(t, b, 1, r, l, -1));
  hs.push_back(Matrixhash(b, t, -1, l, r, 1));
  hs.push_back(Matrixhash(b, t, -1, r, l, -1));
  hs.push_back(Matrixhash2(t, b, 1, l, r, 1));  // 上->下 & 左->右
  hs.push_back(Matrixhash2(t, b, 1, r, l, -1));
  hs.push_back(Matrixhash2(b, t, -1, l, r, 1));
  hs.push_back(Matrixhash2(b, t, -1, r, l, -1));

  auto FindAns = [&hs]() -> bool {
    for (auto v : hs) {
      if (H.count(v)) {
        return true;
      }
    }
    return false;
  };

  if (!FindAns()) {
    char c = 'a' + ansNum;
    ansNum++;
    for (auto v : hs) {
      H[v] = c;
    }
  }
  char c = H[hs[0]];
  for (auto [x, y] : stars) {
    str[x][y] = c;
  }
}

void Solver() {  //
  scanf("%d%d", &m, &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", str[i]);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (str[i][j] == '1') {
        Solver(i, j);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    printf("%s\n", str[i]);
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