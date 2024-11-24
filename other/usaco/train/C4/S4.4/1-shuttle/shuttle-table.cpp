/*
ID: tiankonguse
TASK: shuttle
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "shuttle"
#define TASKEX "-table"

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
int N;
int MAKS;
vector<vector<int>> dp;
vector<vector<tuple<int, int, int>>> path;
int S, T, M;

inline bool W(int p, int mask) { return ((mask >> p) & 1) == 1; }
inline bool B(int p, int mask) { return ((mask >> p) & 1) == 0; }

vector<vector<int>> tableAns;
void Init() {
  tableAns.resize(13);
  tableAns[12] = {
      12, 14, 15, 13, 11, 10, 12, 14, 16, 17, 15, 13, 11, 9,  8,  10, 12,
      14, 16, 18, 19, 17, 15, 13, 11, 9,  7,  6,  8,  10, 12, 14, 16, 18,
      20, 21, 19, 17, 15, 13, 11, 9,  7,  5,  4,  6,  8,  10, 12, 14, 16,
      18, 20, 22, 23, 21, 19, 17, 15, 13, 11, 9,  7,  5,  3,  2,  4,  6,
      8,  10, 12, 14, 16, 18, 20, 22, 24, 25, 23, 21, 19, 17, 15, 13, 11,
      9,  7,  5,  3,  1,  2,  4,  6,  8,  10, 12, 14, 16, 18, 20, 22, 24,
      23, 21, 19, 17, 15, 13, 11, 9,  7,  5,  3,  4,  6,  8,  10, 12, 14,
      16, 18, 20, 22, 21, 19, 17, 15, 13, 11, 9,  7,  5,  6,  8,  10, 12,
      14, 16, 18, 20, 19, 17, 15, 13, 11, 9,  7,  8,  10, 12, 14, 16, 18,
      17, 15, 13, 11, 9,  10, 12, 14, 16, 15, 13, 11, 12, 14, 13};
  tableAns[11] = {
      11, 13, 14, 12, 10, 9,  11, 13, 15, 16, 14, 12, 10, 8,  7,  9,  11, 13,
      15, 17, 18, 16, 14, 12, 10, 8,  6,  5,  7,  9,  11, 13, 15, 17, 19, 20,
      18, 16, 14, 12, 10, 8,  6,  4,  3,  5,  7,  9,  11, 13, 15, 17, 19, 21,
      22, 20, 18, 16, 14, 12, 10, 8,  6,  4,  2,  1,  3,  5,  7,  9,  11, 13,
      15, 17, 19, 21, 23, 22, 20, 18, 16, 14, 12, 10, 8,  6,  4,  2,  3,  5,
      7,  9,  11, 13, 15, 17, 19, 21, 20, 18, 16, 14, 12, 10, 8,  6,  4,  5,
      7,  9,  11, 13, 15, 17, 19, 18, 16, 14, 12, 10, 8,  6,  7,  9,  11, 13,
      15, 17, 16, 14, 12, 10, 8,  9,  11, 13, 15, 14, 12, 10, 11, 13, 12};
  tableAns[10] = {10, 12, 13, 11, 9,  8,  10, 12, 14, 15, 13, 11, 9,  7,  6,
                  8,  10, 12, 14, 16, 17, 15, 13, 11, 9,  7,  5,  4,  6,  8,
                  10, 12, 14, 16, 18, 19, 17, 15, 13, 11, 9,  7,  5,  3,  2,
                  4,  6,  8,  10, 12, 14, 16, 18, 20, 21, 19, 17, 15, 13, 11,
                  9,  7,  5,  3,  1,  2,  4,  6,  8,  10, 12, 14, 16, 18, 20,
                  19, 17, 15, 13, 11, 9,  7,  5,  3,  4,  6,  8,  10, 12, 14,
                  16, 18, 17, 15, 13, 11, 9,  7,  5,  6,  8,  10, 12, 14, 16,
                  15, 13, 11, 9,  7,  8,  10, 12, 14, 13, 11, 9,  10, 12, 11};
  tableAns[9] = {9, 11, 12, 10, 8,  7,  9,  11, 13, 14, 12, 10, 8,  6,  5,
                 7, 9,  11, 13, 15, 16, 14, 12, 10, 8,  6,  4,  3,  5,  7,
                 9, 11, 13, 15, 17, 18, 16, 14, 12, 10, 8,  6,  4,  2,  1,
                 3, 5,  7,  9,  11, 13, 15, 17, 19, 18, 16, 14, 12, 10, 8,
                 6, 4,  2,  3,  5,  7,  9,  11, 13, 15, 17, 16, 14, 12, 10,
                 8, 6,  4,  5,  7,  9,  11, 13, 15, 14, 12, 10, 8,  6,  7,
                 9, 11, 13, 12, 10, 8,  9,  11, 10};
  tableAns[8] = {8,  10, 11, 9,  7,  6,  8,  10, 12, 13, 11, 9, 7, 5, 4,  6,
                 8,  10, 12, 14, 15, 13, 11, 9,  7,  5,  3,  2, 4, 6, 8,  10,
                 12, 14, 16, 17, 15, 13, 11, 9,  7,  5,  3,  1, 2, 4, 6,  8,
                 10, 12, 14, 16, 15, 13, 11, 9,  7,  5,  3,  4, 6, 8, 10, 12,
                 14, 13, 11, 9,  7,  5,  6,  8,  10, 12, 11, 9, 7, 8, 10, 9};
}

void Solver() {  //
  scanf("%d", &n);
  Init();

  vector<int> ans;
  if (n < 8) {
    N = n * 2 + 1;
    MAKS = 1 << N;
    dp.resize(N, vector<int>(MAKS, -1));
    path.resize(N, vector<tuple<int, int, int>>(MAKS));
    // WWWW BBB => 1110000
    S = (1 << n) - 1;
    T = S << (n + 1);
    M = n;
    queue<pair<int, int>> que;
    que.push({M, S});
    dp[M][S] = 0;

    auto CheckFinish = [&que](int newP, int newMask, int movePos, int p,
                              int mask) {
      if (dp[newP][newMask] != -1) {
        return false;
      }
      dp[newP][newMask] = dp[p][mask] + 1;
      que.push({newP, newMask});
      path[newP][newMask] = {movePos, p, mask};
      // printf("search: [%d][%o] => [%d][%o] move=%d cost=%d\n", p, mask, newP,
      //        newMask, movePos, dp[newP][newMask]);
      if (newMask == T && newP == M) {
        return true;
      }
      return false;
    };

    while (!que.empty()) {
      const auto [p, mask] = que.front();
      que.pop();

      // left  ?WB ? => ? BW?
      if (p >= 1 && W(p - 2, mask) && B(p - 1, mask)) {
        int newMask = mask ^ (1 << (p - 2)) ^ (1 << p);
        int newP = p - 2;
        if (CheckFinish(newP, newMask, p - 2, p, mask)) {
          break;
        }
      }

      // left ?W ? => ? W?
      if (p >= 1 && W(p - 1, mask)) {
        int newMask = mask ^ (1 << (p - 1)) ^ (1 << p);
        int newP = p - 1;
        if (CheckFinish(newP, newMask, p - 1, p, mask)) {
          break;
        }
      }

      // right ? B? => ?B ?
      if (p < N - 1 && B(p + 1, mask)) {
        int newMask = mask;
        int newP = p + 1;
        if (CheckFinish(newP, newMask, p + 1, p, mask)) {
          break;
        }
      }

      // right ? WB? => ?BW ?
      if (p < N - 2 && W(p + 1, mask) && B(p + 2, mask)) {
        int newMask = mask;
        int newP = p + 2;
        if (CheckFinish(newP, newMask, p + 2, p, mask)) {
          break;
        }
      }
    }

    int num = dp[M][T];
    assert(num > 0);
    ans.reserve(num);

    int p = M;
    int mask = T;
    while (true) {
      auto [movePos, preP, preMask] = path[p][mask];

      // printf("path: [%d][%o] => [%d][%o] move=%d cost=%d\n", p, mask, preP,
      //        preMask, movePos, dp[p][mask]);
      ans.push_back(movePos + 1);
      p = preP;
      mask = preMask;
      if (p == M && mask == S) break;
    }
    std::reverse(ans.begin(), ans.end());
  } else {
    ans = tableAns[n];
  }

  int num = ans.size();
  for (int i = 1; i <= num; i++) {
    printf("%d%c", ans[i - 1], (i % 20 == 0 || i == num) ? '\n' : ' ');
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