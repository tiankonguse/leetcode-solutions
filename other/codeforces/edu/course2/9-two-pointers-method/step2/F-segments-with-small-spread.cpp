/*
ID: tiankonguse
TASK: F. Segments with Small Spread F. 价差较小的细分市场
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/F
PATH: ITMO Academy: pilot course » Two Pointers Method » Step 2 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/
*/
#define TASK "F-segments-with-small-spread"
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

int n;
ll m;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d%lld", &n, &m);
}

vector<ll> A, B, C;
void Solver() {  //
  A.reserve(n + 1);
  for (int i = 0; i < n; i++) {
    ll v;
    scanf("%lld", &v);
    A.push_back(v);
  }
  ll ans = 0;
  int r = 0;
  map<ll, int> H;
  auto Dis = [](map<ll, int>& H) -> ll {
    if (H.empty()) return 0;
    const ll minVal = H.begin()->first;
    const ll maxVal = H.rbegin()->first;
    return maxVal - minVal;
  };
  for (int l = 0; l < n; l++) {
    while (r < n && Dis(H) <= m) {  // [l, r)
      H[A[r]]++;
      r++;
    }
    if (Dis(H) > m) {  // A[r-1] 加入后不满足
      ans += r - 1 - l;
    } else {  // 都满足
      ans += r - l;
    }
    H[A[l]]--;
    if (H[A[l]] == 0) {
      H.erase(A[l]);
    }
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