/*
ID: tiankonguse
TASK: demo
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "C-v2"
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


const ll mod = 2933256077ll;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

const int N = 3e6 + 10;
int n, m;
char str[N];
void InitIO() {
  // #ifdef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
  scanf("%d%d%s", &n, &m, str);
}

ll dp[222][111][111];  // f(p, nn, mm) 前 p 个匹配，剩余  mm 个 0 与 nn 个 1 时的最优答案
ll Dfs(const int i, int nm[]) {
  if (nm[0] + nm[1] == 0) {
    return i;
  }
  ll& ret = dp[i][nm[0]][nm[1]];
  if (ret != -1) return ret;

  ret = 0;

  const int v = str[i] - '0';
  if (nm[v] > 0) {  // 匹配
    nm[v]--;
    ret = Dfs(i + 1, nm);

    const int oldV = nm[1 - v];
    while (nm[1 - v] > 0) {
      nm[1 - v]--;
      ret = (ret + Dfs(i + 1, nm)) % mod;  // skip 不匹配的
    }
    nm[1 - v] = oldV;
    nm[v]++;
  } else {
    ret = i;  // 没有匹配的字符了， 后面的全部是 1-v
  }

  return ret;
}
void Solver() {  //
  for (int i = 0; i <= n + m; i++) {
    for (int j = 0; j <= m; j++) {
      for (int k = 0; k <= n; k++) {
        dp[i][j][k] = -1;
      }
    }
  }
  int nm[] = {m, n};
  printf("%lld\n", Dfs(0, nm));
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