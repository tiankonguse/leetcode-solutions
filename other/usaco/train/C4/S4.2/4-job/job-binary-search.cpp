/*
ID: tiankonguse
TASK: job
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "job"
#define TASKEX "-binary-search"

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

int n, ma, mb;
int A[33], B[33];
int t1, t2;

vector<int> costA;

bool Check(const int T) {
  min_queue<pair<int, int>> busyQueB;
  min_queue<int> freeQueB;

  auto FastTimeB = [&busyQueB, &freeQueB](const int t) {
    while (!busyQueB.empty() && busyQueB.top().first <= t) {
      freeQueB.push(busyQueB.top().second);
      busyQueB.pop();
    }
  };

  for (int i = 0; i < mb; i++) {
    // printf("add %d\n", -B[i]);
    freeQueB.push(-B[i]);
  }
  int t = 0;
  for (auto ta : costA) {  // t 时刻来了一个任务
    t = max(t, ta);
    FastTimeB(t);

    while (true) {
      if (freeQueB.empty()) {
        if (busyQueB.empty()) return false;
        t = busyQueB.top().first;
        FastTimeB(t);
      }
      const auto b = freeQueB.top();
      freeQueB.pop();
      const int cost = -b;
      // printf("pop free b=%d ta=%d cost=%d T=%d\n", b, ta, cost, T);

      if (t + cost <= T) {
        // printf("use %d, t=%d->%d\n", b, ta, ta + cost);
        busyQueB.push({t + cost, b});
        break;
      } else {
        // printf("skip %d, ta=%d + cost=%d > T=%d\n", b, ta, cost, T);
      }
    }
  }
  return true;
};

void Solver() {  //
  scanf("%d%d%d", &n, &ma, &mb);

  min_queue<pair<int, int>> busyQueA;
  for (int i = 0; i < ma; i++) {
    scanf("%d", &A[i]);
    busyQueA.push({A[i], A[i]});  // 时间相同时，选择性能最高的机器
  }
  for (int i = 0; i < mb; i++) {
    scanf("%d", &B[i]);
  }

  // 对于 A，所有选择是确定的
  costA.resize(n, 0);
  for (int i = 0; i < n; i++) {
    auto [t, a] = busyQueA.top();
    busyQueA.pop();
    busyQueA.push({t + a, a});
    costA[i] = t;
    // printf("costA[%d]=%d\n", i, t);
  }
  t1 = costA.back();

  // Check(5);

  int l = 1, r = 44000;
  while (l < r) {
    int mid = (l + r) / 2;
    if (Check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  t2 = r;

  printf("%d %d\n", t1, t2);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/