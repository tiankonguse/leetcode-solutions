/*
ID: tiankonguse
TASK: fence8
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "fence8"
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

int N, R;
vector<int> rails;
map<int, int> stat;
vector<int> preSums;
int boardSum = 0;

bool Dfs(int r, int preV, int searchV) {
  if (r == 0) {
    return true;
  }
  if (preSums[r] > boardSum) return false;  // 总长度剪枝

  const int v = rails[r - 1];
  bool OK = false;

  if (stat.empty()) return false;
  auto it = stat.end();
  it--;

  if (v == preV) {  // 搜索的值相等，接着之前的开始搜索
    it = stat.upper_bound(searchV);
    if (it == stat.begin()) return false;
    it--;
  }
  while (it->first >= v && !OK) {
    const auto [V, L] = *it;
    const int leftV = V - v;
    assert(L > 0);

    boardSum -= V;
    if (L == 1) {
      stat.erase(V);
    } else {
      stat[V]--;
    }
    if (leftV > 0) {
      stat[leftV]++;
      if (leftV >= rails.front()) {
        boardSum += leftV;
      }
    }

    if (Dfs(r - 1, v, V)) {
      OK = true;
    }

    boardSum += V;
    stat[V] = L;
    if (leftV > 0) {
      stat[leftV]--;
      if (stat[leftV] == 0) {
        stat.erase(leftV);
      }
      if (leftV >= rails.front()) {
        boardSum -= leftV;
      }
    } else {
      break;  // 贪心选择相等的
    }
    it = stat.lower_bound(V);
    if (it == stat.begin()) break;
    it--;
  }
  return OK;
}

int Check() {
  boardSum = 0;
  for (auto [V, L] : stat) {
    if (V >= rails.front()) {
      boardSum += V * L;
    }
  }

  preSums.resize(R + 1, 0);
  for (int i = 1; i <= R; i++) {
    preSums[i] = preSums[i - 1] + rails[i - 1];
    if (!Dfs(i, -1, -1)) {
      return i - 1;
    }
  }
  return R;
}

void Solver() {  //
  scanf("%d", &N);
  stat.clear();
  for (int i = 0; i < N; i++) {
    int v;
    scanf("%d", &v);
    stat[v]++;
  }

  scanf("%d", &R);
  rails.resize(R);
  for (int i = 0; i < R; i++) {
    scanf("%d", &rails[i]);
  }
  sort(rails.begin(), rails.end());

  printf("%d\n", Check());
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/