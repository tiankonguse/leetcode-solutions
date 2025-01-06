/*
ID: tiankonguse
TASK: H. Hamburgers  H.汉堡包
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/H
PATH: ITMO Academy: pilot course » Binary Search » Step 2 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
*/
#define TASK "H-hamburgers"
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

template <class T> using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T> using max_queue = priority_queue<T>;

char readWritebuf[1000];
inline ll FastRead() {
  scanf("%s", readWritebuf);
  ll v = 0;
  const char* p = readWritebuf;
  while (*p) {
    v = v * 10 + (*p - '0');
    p++;
  }
  return v;
}
inline void FastWrite(ll v) {
  char* p = readWritebuf;
  if (v == 0) {
    *p = '0';
    p++;
  }
  while (v) {
    *p = '0' + (v % 10);
    v /= 10;
    p++;
  }
  std::reverse(readWritebuf, p);
  *p = '\0';
  printf("%s", readWritebuf);
}

char str[111];
ll nBSC[3];
ll pBSC[3];
ll R;

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo.out", "w", stdout);
#endif
  scanf("%s", str);
  for (int i = 0; i < 3; i++) {
    nBSC[i] = FastRead();
  }
  for (int i = 0; i < 3; i++) {
    pBSC[i] = FastRead();
  }
  R = FastRead();
}

ll BSC[3] = {0, 0, 0};
void InitData() {
  map<char, int> h = {{'B', 0}, {'S', 1}, {'C', 2}};
  int n = strlen(str);
  for (int i = 0; i < n; i++) {
    BSC[h[str[i]]]++;
  }
}

bool Check(ll x) {  //
  ll bsc[3] = {0, 0, 0};
  for (int i = 0; i < 3; i++) {
    bsc[i] = BSC[i] * x;
  }

  ll sum = 0;
  for (int i = 0; i < 3; i++) {
    if (nBSC[i] >= bsc[i]) continue;  // 不需要购买
    sum += (bsc[i] - nBSC[i]) * pBSC[i];
  }

  return sum <= R;
}

ll Search() {
  ll l = 0, r = R + 300;
  while (l < r) {  // [l,r)
    auto m = (l + r) / 2;
    if (Check(m)) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  return r - 1;
}
void Solver() {  //
  InitData();
  FastWrite(Search());
  printf("\n");
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