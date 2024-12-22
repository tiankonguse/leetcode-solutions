/*
ID: tiankonguse
TASK: C 割
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/contest/210959
PATH:【LGR-210-Div.3】洛谷基础赛 #19 & ALFR Round 3
submission:
*/
#define TASK "C"
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

int n, k;
const int N = 2e5 + 10;
char str[N];
void InitIO() {  //
  // #ifdef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
  scanf("%d%d", &n, &k);
  scanf("%s", str);
}

string ans;
vector<int> sufMaxVal;
void SolverEx() {
  char maxVal = 'a' - 1;
  int maxNum = 0;
  int lastPos = -1;
  for (int i = 0; i < n; i++) {
    char c = str[i];
    if (maxVal < c) {
      maxVal = c;
      maxNum = 0;
    }
    if (maxVal == c) {
      maxNum++;
      lastPos = i;
    }
  }
  if (n == 1) {
    ans.push_back(maxVal);
    return;
  }

  int num = maxNum / k;
  if (maxNum % k != 0) {
    ans.resize(num + 1, maxVal);
    return;
  }
  ans.reserve(n);
  ans.resize(num, maxVal);
  if (lastPos + 1 < n) {  //
    sufMaxVal.resize(n + 1, 0);
    sufMaxVal[n - 1] = n - 1;
    for (int i = n - 2; i > lastPos; i--) {
      const int maxValpos = sufMaxVal[i + 1];
      if (str[i] >= str[maxValpos]) {
        sufMaxVal[i] = i;
      } else {
        sufMaxVal[i] = maxValpos;
      }
    }
    while (lastPos + 1 < n) {
      lastPos = sufMaxVal[lastPos + 1];
      ans.push_back(str[lastPos]);
    }
  }
}
void Solver() {  //
  SolverEx();
  printf("%s\n", ans.data());
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my =
      std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(
          t2 - t1);
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