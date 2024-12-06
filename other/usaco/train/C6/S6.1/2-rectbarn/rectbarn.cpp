/*
ID: tiankonguse
TASK: rectbarn
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "rectbarn"
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

int n, m, P;
vector<pair<int, int>> ps;
vector<int> rows, leftPos, rightPos;
vector<pair<int, int>> orderedQue;
void Solver() {  //
  scanf("%d%d%d", &n, &m, &P);
  ps.resize(P);
  for (int i = 0; i < P; i++) {
    scanf("%d%d", &ps[i].first, &ps[i].second);
  }
  sort(ps.begin(), ps.end());

  ll ans = 0;
  rows.resize(m + 10, 0);
  orderedQue.resize(m + 1);

  int p = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      rows[j]++;
    }
    while (p < P && ps[p].first == i) {  // 障碍物，高度至 0
      const int y = ps[p].second;
      rows[y] = 0;
      p++;
    }

    leftPos.clear();
    leftPos.resize(m + 1, 0);

    orderedQue.clear();
    orderedQue.push_back({-1, 0});  // 不可能出对
    for (int j = 1; j <= m; j++) {
      const ll h = rows[j];
      int pos = j;
      while (h <= orderedQue.back().first) {
        pos = orderedQue.back().second;
        orderedQue.pop_back();
      }
      leftPos[j] = pos;
      orderedQue.push_back({h, pos});
    }

    rightPos.clear();
    rightPos.resize(m + 1, 0);

    orderedQue.clear();
    orderedQue.push_back({-1, m + 1});  // 不可能出对
    for (int j = m; j >= 1; j--) {
      const ll h = rows[j];
      int pos = j;
      while (h <= orderedQue.back().first) {
        pos = orderedQue.back().second;
        orderedQue.pop_back();
      }
      rightPos[j] = pos;
      orderedQue.push_back({h, pos});
    }

    for (int j = 1; j <= m; j++) {  // 枚举 r 为最低点，二分左右最远距离
      const ll h = rows[j];
      const int L = leftPos[j];
      const int R = rightPos[j];
      //   printf("i=%d j=%d h=%lld L=%d R=%d tmp=%lld\n", i, j, h, L, R,
      //          (R - L + 1) * h);
      ans = max(ans, (R - L + 1) * h);
    }
  }

  printf("%lld\n", ans);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*
Executing...
   Test 1: TEST OK [0.004 secs limit:1s, 1804 KB]
   Test 2: TEST OK [0.004 secs limit:1s, 1700 KB]
   Test 3: TEST OK [0.004 secs limit:1s, 1720 KB]
   Test 4: TEST OK [0.011 secs limit:1s, 1712 KB]
   Test 5: TEST OK [0.014 secs limit:1s, 1680 KB]
   Test 6: TEST OK [0.060 secs limit:1.5s, 1688 KB]
   Test 7: TEST OK [0.074 secs limit:1.5s, 1712 KB]
   Test 8: TEST OK [0.410 secs limit:2s, 3204 KB]
   Test 9: TEST OK [0.605 secs limit:2s, 3316 KB]
   Test 10: TEST OK [0.612 secs limit:2s, 3220 KB]
*/