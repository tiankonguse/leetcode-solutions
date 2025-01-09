/*
ID: tiankonguse
TASK: B. Minimum Average Path  B. 最小平均路径
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/6/4/practice/contest/285069/problem/B
PATH: ITMO Academy: pilot course » Binary Search » Step 4 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
*/
#define TASK "B-minimum-average-path"
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

template <class T> using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T> using max_queue = priority_queue<T>;

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

ll n, m;
vector<vector<pair<int, int>>> g;

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo.out", "w", stdout);
#endif
  scanf("%lld%lld", &n, &m);
  g.resize(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    g[a].push_back({b, c});
  }
}

void InitData() {}

//  Probably, the solution is executed with error 'signed integer overflow' on the line 97
// 转化为整形，会越界
const ll A = 1e9;
const ll N = 1e5;

vector<ll> preFlag;
int ansL, ansR;
bool debugFlag = 0;
bool Eq(double a, double b) { return (a - eps <= b && b <= a + eps); }

vector<double> preSum;
vector<int> preFrom;

struct DoubleGreater {
  typedef pair<double, int> _Tp;                           // used by valarray
  bool operator()(const _Tp& __x, const _Tp& __y) const {  //
    return __x.first > __y.first + eps;
  }
};

priority_queue<pair<double, int>, vector<pair<double, int>>, DoubleGreater> que;
bool Check(const double avg) {  //
  preSum.clear();
  preFrom.clear();
  preSum.resize(n + 1, INT_MAX);
  preFrom.resize(n + 1, -1);
  while (!que.empty()) que.pop();
  que.push({0, 1});
  preSum[1] = 0;
  preFrom[1] = 1;

  while (!que.empty()) {
    const auto [d, u] = que.top();
    que.pop();
    // printf("u=%d d=%lf preSum[u]=%lf\n", u, d, preSum[u]);
    if (preSum[u] + eps < d) {
      // printf("skip\n");
      continue;  // 已经有更优答案了
    }
    for (const auto& [v, c] : g[u]) {
      const double C = c - avg;
      const double D = d + C;
      // printf("u[%d]->v[%d] D=%lf preSum[v]=%lf\n", u, v, D, preSum[v]);
      if (D + eps < preSum[v]) {
        preSum[v] = D;  // 越小越好
        preFrom[v] = u;
        que.push({D, v});
      }
      if (v == n && preSum[v] + eps <= 0) {
        // printf("true\n");
        return true;
      }
    }
  }

  return false;
}

vector<int> paths;
void Search() {
  // printf("Search\n");
  // Check(50000.500000);
  // return;
  double l = 0, r = 100;
  while (l + eps < r) {  // [l,r)
    auto m = (l + r) / 2;
    if (Check(m)) {  // 是否存在一个 path, avg <= m
      // printf("m=%lf l=%lf r=%lf\n", m, l, r);
      r = m;
    } else {
      // printf("m=%lf \n", m);
      l = m + eps;
    }
  }
  if (r <= eps) {
    r = 0;
    Check(r);
  } else {
    Check(r - eps);
  }

  paths.reserve(n + 1);
  paths.clear();
  paths.push_back(n);
  int now = n;
  while (now != 1) {
    now = preFrom[now];
    paths.push_back(now);
  }
  std::reverse(paths.begin(), paths.end());
}
void Solver() {  //
  InitData();
  Search();

  int k = paths.size();
  printf("%d\n", k - 1);
  for (int i = 0; i < k; i++) {
    printf("%d%c", paths[i], i + 1 == k ? '\n' : ' ');
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