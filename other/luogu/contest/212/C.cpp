/*
ID: tiankonguse
TASK: demo
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
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

const int N = 3e6 + 10;
int n, m;
char str[N];
void InitIO() {  //
                 // #ifdef USACO_LOCAL_JUDGE
                 //   freopen(TASK ".in", "r", stdin);
                 //   freopen(TASK ".out", "w", stdout);
                 // #endif
  scanf("%d%d%s", &n, &m, str);
}

ll ans = 0;
string buf;

int Check() {
  int nm = n + m;
  int j = 0;
  for (int i = 0; i < nm; i++) {
    while (j < nm && buf[j] != str[i]) {
      j++;
    }
    if (j == nm) return i;
    j++;
  }
  return nm;
}

vector<int> preNum;
void Dfs(int i, int nn, int mm) {
  if (i == n + m) {
    int len = Check();
    preNum[len]++;
    if (len == 3) {
      printf("3: %s\n", buf.data());
    }
    ans += len;
    return;
  }
  // 选择相同
  if (nn < n) {
    buf.push_back('1');
    Dfs(i + 1, nn + 1, mm);
    buf.pop_back();
  }

  if (mm < m) {
    buf.push_back('0');
    Dfs(i + 1, nn, mm + 1);
    buf.pop_back();
  }
}
void Solver() {  //
  buf.reserve(m + n);
  preNum.resize(m + n + 1, 0);
  Dfs(0, 0, 0);
  for (int i = 0; i <= n + m; i++) {
    printf("len=%d num=%d ans=%d\n", i, preNum[i], i * preNum[i]);
  }
  printf("%lld\n", ans);
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