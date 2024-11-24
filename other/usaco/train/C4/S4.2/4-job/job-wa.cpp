/*
ID: tiankonguse
TASK: job
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "job"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK);
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

void Solver() {  //
  int n1, m1, m2, n2 = 0, n3 = 0;
  scanf("%d%d%d", &n1, &m1, &m2);
  const int N = n1;

  min_queue<int> freeQue1, freeQue2;
  min_queue<pair<int, int>> busyQue1, busyQue2;

  for (int i = 0; i < m1; i++) {
    int t;
    scanf("%d", &t);
    freeQue1.push(t);
  }
  for (int i = 0; i < m2; i++) {
    int t;
    scanf("%d", &t);
    freeQue2.push(t);
  }

  int t1 = 0;
  int t2 = 0;
  for (int t = 0; n3 != N; t++) {
    // 机器1 完成释放出来
    while (!busyQue1.empty() && busyQue1.top().first == t) {
      int v = busyQue1.top().second;
      busyQue1.pop();
      freeQue1.push(v);
      n2++;
    }

    // 机器1 分配任务
    while (!freeQue1.empty() && n1 > 0) {
      int v = freeQue1.top();
      freeQue1.pop();
      busyQue1.push({t + v, v});
      n1--;
    }

    // 机器1首次闲着，A完成
    if (busyQue1.empty() && t1 == 0) {
      t1 = t;
    }

    // 机器2 完成释放出来
    while (!busyQue2.empty() && busyQue2.top().first == t) {
      int v = busyQue2.top().second;
      busyQue2.pop();
      freeQue2.push(v);
      n3++;
    }
    // 机器2 分配任务
    while (!freeQue2.empty() && n2 > 0) {
      int v = freeQue2.top();
      freeQue2.pop();
      busyQue2.push({t + v, v});
      n2--;
    }

    // 机器1首次闲着，A完成
    if (busyQue1.empty() && busyQue2.empty()) {
      t2 = t;
    }
  }
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