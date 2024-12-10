/*
ID: tiankonguse
TASK: wissqu
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "wissqu"
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

int leftV[6] = {0, 3, 3, 3, 4, 3};
char str[6][6];
int mask[6][6][6];
int oldGrid[6][6];
int newGrid[6][6];
const int N = 5;

int ans = 0;
string ansBuf;
string buf;
void FillMask(int x, int y, int v) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      //   if (i == 0 && j == 0) continue;
      mask[x + i][y + j][v]++;
    }
  }
}
void UnFillMask(int x, int y, int v) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      //   if (i == 0 && j == 0) continue;
      mask[x + i][y + j][v]--;
    }
  }
}

ll CalHash(ll h, ll v, int x, int y) {
  x--, y--;
  int offset = x * 4 + y;
  return h | (v << (offset * 3));
}

ll Dfs(int p, ll h);
ll Dfs(const int p, const int v, const ll h) {
  int ret = 0;
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
      if (newGrid[i][j]) continue;      // 已选择
      if (mask[i][j][v]) continue;      // 冲突
      UnFillMask(i, j, oldGrid[i][j]);  // 移出旧的值
      newGrid[i][j] = v;
      buf.push_back('A' + (v - 1));
      buf.push_back('0' + i);
      buf.push_back('0' + j);
      FillMask(i, j, newGrid[i][j]);
      ret += Dfs(p + 1, CalHash(h, v, i, j));
      UnFillMask(i, j, newGrid[i][j]);
      buf.pop_back();
      buf.pop_back();
      buf.pop_back();
      newGrid[i][j] = 0;
      FillMask(i, j, oldGrid[i][j]);
    }
  }
  return ret;
}

unordered_map<ll, ll> H;
ll Dfs(const int p, const ll h) {
  if (p == 17) {
    if (ansBuf.empty()) {
      ansBuf = buf;
    }
    return 1;
  }
  if (H.count(h)) return H[h];
  ll& ret = H[h];
  for (int i = 1; i <= N; i++) {
    if (leftV[i] == 0) continue;
    leftV[i]--;
    ret += Dfs(p, i, h);  // 第p个字符，选择字母 i
    leftV[i]++;
  }
  return ret;
}

void Solver() {  //
  memset(oldGrid, 0, sizeof(oldGrid));
  memset(newGrid, 0, sizeof(newGrid));
  memset(mask, 0, sizeof(mask));

  for (int i = 1; i <= 4; i++) {
    scanf("%s", str[i] + 1);
    for (int j = 1; j <= 4; j++) {
      int v = str[i][j] - 'A' + 1;
      oldGrid[i][j] = v;
      FillMask(i, j, v);
    }
  }
  leftV[4]--;
  ans = Dfs(1, 4, 0);

  int i = 0;
  for (auto c : ansBuf) {
    i++;
    printf("%c%c", c, i % 3 == 0 ? '\n' : ' ');
  }

  printf("%d\n", ans);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*
Executing...
   Test 1: TEST OK [0.011 secs limit:5s, 3312 KB]

All tests OK.
*/