/*
ID: tiankonguse
TASK: D. Minimum maximum on the Path D. 路径上的最小最大值
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/D
PATH: ITMO Academy: pilot course » Binary Search » Step 3 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
*/
#define TASK "D-minimum-maximum-on-the-path"
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

ll n, m, d;
vector<vector<pair<ll, ll>>> g;

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo.out", "w", stdout);
#endif
  scanf("%lld%lld%lld", &n, &m, &d);
  g.resize(n + 1);
  for (int i = 0; i < m; i++) {
    ll a, b, c;
    scanf("%lld%lld%lld", &a, &b, &c);
    g[a].push_back({b, c});
  }
}

void InitData() {}

//  Probably, the solution is executed with error 'signed integer overflow' on the line 97
// 转化为整形，会越界
const ll A = 1e9;
const ll N = 1e5;
vector<ll> paths;

vector<ll> preFlag;
bool Check(ll C) {  //
  preFlag.clear();
  preFlag.resize(n + 1, -1);

  queue<pair<ll, ll>> que;
  que.push({0, 1});
  preFlag[1] = 0;

  while (!que.empty()) {
    const auto [D, a] = que.front();
    que.pop();
    for (auto [b, c] : g[a]) {
      if (c > C) continue;
      if (preFlag[b] != -1) continue;
      if (D + 1 > d) continue;
      que.push({D + 1, b});
      preFlag[b] = a;
    }
  }
  if (preFlag[n] == -1) return false;

  return true;
}

ll Search() {
  preFlag.reserve(n + 1);  // 初始化内存，避免频繁扩容

  ll l = 0, r = A;
  while (l < r) {  // [l,r)
    auto m = (l + r) / 2;
    if (Check(m)) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  if (Check(r)) {  // 找到答案后，重新搜索，记录答案
    paths.reserve(n);  // 初始化内存，避免频繁扩容
    int now = n;
    paths.push_back(now);
    while (now != 1) {
      now = preFlag[now];
      paths.push_back(now);
    }
    std::reverse(paths.begin(), paths.end());
  }

  return paths.size();
}
void Solver() {  //
  InitData();
  Search();
  int num = paths.size();
  if (num == 0) {
    printf("-1\n");
  } else {
    printf("%d\n", num - 1);
    for (int i = 0; i < num; i++) {
      printf("%lld%c", paths[i], i + 1 == num ? '\n' : ' ');
    }
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