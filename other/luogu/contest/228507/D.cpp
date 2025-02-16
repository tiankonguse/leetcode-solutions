/*
ID: tiankonguse
TASK: 谢谢您。
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "D"
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

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
}

int n, m, q;
vector<int> nums;
vector<pair<int, int>> sections;
void Solver() {  //
  scanf("%d%d%d", &n, &m, &q);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
  }
  sections.resize(m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &sections[i].first, &sections[i].second);
  }
  while (q--) {
    int L, R, k;
    scanf("%d%d%d", &L, &R, &k);
    int ans = 0;
    for (int i = L - 1; i < R; i++) {
      int sum = 0;
      for (int j = sections[i].first - 1; j < sections[i].second; j++) {
        if (nums[j] == k) {
          sum++;
        }
      }
      // printf("i=%d sum=%d\n", i, sum);
      ans = max(ans, sum);
    }
    printf("%d\n", ans);
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