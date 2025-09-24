/*
ID: tiankonguse
TASK: snakes
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P7078
PATH: P7078 [CSP-S2020] 贪吃蛇
submission:
*/
#define TASK "snakes"
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

#ifdef USACO_LOCAL_JUDGE
int debug_log = 0;
int debug_assert = 1;
#define MyPrintf(...)                   \
  do {                                  \
    if (debug_log) printf(__VA_ARGS__); \
  } while (0)

#define MyAssert(...)                      \
  do {                                     \
    if (debug_assert) assert(__VA_ARGS__); \
  } while (0)
#else
#define MyPrintf(...)
#define MyAssert(...)
#endif

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
#define TASKNO "3"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

int n;
vector<ll> A;
deque<pair<ll, ll>> que[2];

tuple<ll, ll, ll> GetMax() {
  int ii = -1;
  for (int i = 0; i < 2; i++) {
    if (que[i].empty()) {
      ii = 1 - i;
      break;
    }
  }
  if (ii == -1) {
    if (que[0].back() > que[1].back()) {
      ii = 0;
    } else {
      ii = 1;
    }
  }
  auto [val, idx] = que[ii].back();
  que[ii].pop_back();
  return {val, idx, ii};
}
tuple<ll, ll, ll> GetMin() {
  int ii = -1;
  for (int i = 0; i < 2; i++) {
    if (que[i].empty()) {
      ii = 1 - i;
      break;
    }
  }
  if (ii == -1) {
    if (que[0].front() < que[1].front()) {
      ii = 0;
    } else {
      ii = 1;
    }
  }

  auto [val, idx] = que[ii].front();
  que[ii].pop_front();
  return {val, idx, ii};
}

bool Check() {  // 最小值是否被吃
  int leftNum = que[0].size() + que[1].size();
  if (leftNum <= 1) return false;
  if (leftNum == 2) return true;  // 被吃
  auto [maxVal, maxIdx, maxType] = GetMax();
  auto [minVal, minIdx, minType] = GetMin();
  auto [secondMinVal, secondMinIdx, secondMinType] = GetMin();
  if (maxVal - minVal > secondMinVal || (maxVal - minVal == secondMinVal && maxIdx > secondMinIdx)) {
    return true;
  }
  que[secondMinType].push_front({secondMinVal, secondMinIdx});
  que[1].push_front({maxVal - minVal, maxIdx});
  return !Check();
}

ll SolverEx() {
  while (!que[0].empty()) que[0].pop_back();
  while (!que[1].empty()) que[1].pop_back();
  for (int i = 0; i < n; i++) {
    que[0].push_back({A[i], i});  // 左小右大
  }
  ll ans = 0;
  while (que[0].size() + que[1].size() >= 3) {  // 必吃
    auto [maxVal, maxIdx, maxType] = GetMax();
    auto [minVal, minIdx, minType] = GetMin();
    auto [secondMinVal, secondMinIdx, secondMinType] = GetMin();
    if (maxVal - minVal > secondMinVal || (maxVal - minVal == secondMinVal && maxIdx > secondMinIdx)) {
      que[1].push_front({maxVal - minVal, maxIdx});
      que[secondMinType].push_front({secondMinVal, secondMinIdx});
      ans++;
    } else {
      que[secondMinType].push_front({secondMinVal, secondMinIdx});
      que[minType].push_front({minVal, minIdx});
      que[maxType].push_back({maxVal, maxIdx});
      break;
    }
  }
  if (que[0].size() + que[1].size() == 2) {
    ans++;
  } else {  // 可能不吃
    if (Check()) {
      ans++;
    }
  }
  return ans;
}

void Solver() {  //
  int T;
  scanf("%d", &T);
  int firstCase = 1;
  while (T--) {
    if (firstCase) {
      firstCase = 0;
      scanf("%d", &n);
      A.resize(n);
      for (int i = 0; i < n; i++) {
        scanf("%lld", &A[i]);
      }
    } else {
      int k;
      scanf("%d", &k);
      while (k--) {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        A[x - 1] = y;
      }
    }
    printf("%lld\n", n - SolverEx());
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