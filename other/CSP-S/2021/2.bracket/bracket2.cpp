/*
ID: tiankonguse
TASK: bracket
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P7914
PATH:
submission:
*/
#define TASK "bracket"
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
int n, k;
char str[600];
vector<vector<ll>> dp;
vector<vector<ll>> dpBracket;  // (), 必须是左右括号
vector<vector<ll>> dpLeft;     // *A, 至少1个星
vector<vector<ll>> dpRight;    // A*, 至少1个星
vector<int> preStarts, sufStarts;
// const ll mod = 1e9 + 7;

bool IsStart(int l) { return str[l] == '*' || str[l] == '?'; }
bool MatchLeftBracket(int l) { return str[l] == '(' || str[l] == '?'; }
bool MatchRightBracket(int r) { return str[r] == ')' || str[r] == '?'; }

bool IsAllStar(int l, int r) { return preStarts[r] - preStarts[l - 1] == r - l + 1; }

ll Dfs(int l, int r);  // [l,r]；

ll DfsLeft(const int l, const int r) {
  if (l > r) return 0;
  ll& ret = dpLeft[l][r];
  if (ret != -1) return ret;
  if (r - l + 1 < 3) return ret = 0;

  ret = 0;  // 至少1个，至多 k 个
  for (int i = 1; IsStart(l + i - 1) && i <= k && l + i <= r; i++) {
    ret = (ret + Dfs(l + i, r)) % mod;
  }
  return ret;
}

ll DfsRight(const int l, const int r) {
  if (l > r) return 0;
  ll& ret = dpRight[l][r];
  if (ret != -1) return ret;
  if (r - l + 1 < 3) return ret = 0;

  ret = 0;  // 至少1个，至多 k 个
  for (int i = 1; IsStart(r - i + 1) && i <= k && l <= r - i; i++) {
    ret = (ret + Dfs(l, r - i)) % mod;
  }
  return ret;
}

ll DfsBracket(int l, int r) {
  if (l > r) return 0;
  ll& ret = dpBracket[l][r];
  if (ret != -1) return ret;
  if (l == r) return ret = 0;
  if (!MatchLeftBracket(l)) return ret = 0;
  if (!MatchRightBracket(r)) return ret = 0;
  ret = 0;
  // case: ()
  if (l + 1 == r) return ret = 1;

  // case: (*)
  if (IsAllStar(l + 1, r - 1) && r - l - 1 <= k) {
    ret = (ret + 1) % mod;
  }

  // case: (A)
  ret = (ret + Dfs(l + 1, r - 1)) % mod;

  // case: (*A)
  ret = (ret + DfsLeft(l + 1, r - 1)) % mod;

  // case: (A*)
  ret = (ret + DfsRight(l + 1, r - 1)) % mod;

  return ret;
}

ll Dfs(const int l, const int r) {  // [l,r]
  if (l > r) return 0;
  // 出口
  ll& ret = dp[l][r];
  if (ret != -1) return ret;
  if (l == r) return ret = 0;
  if (!MatchLeftBracket(l)) return ret = 0;
  if (!MatchRightBracket(r)) return ret = 0;
  if (l + 1 == r) return ret = 1;

  ret = 0;
  // case: (...)
  ret = (ret + DfsBracket(l, r)) % mod;

  // case: AB
  // bad case: ABCD, 只需要枚举到 A，故 A 必须是左右括号
  for (int i = l + 1; i + 1 < r; i++) {
    ret = (ret + DfsBracket(l, i) * Dfs(i + 1, r) % mod) % mod;
  }
  // case: A*B
  // bad case: AB*C, A*BC, AB*CD
  for (int i = l + 1; i + 1 <= r; i++) {
    ret = (ret + DfsBracket(l, i) * DfsLeft(i + 1, r) % mod) % mod;
  }

  return ret;
}

void Init() {
  dp.resize(n + 1, vector<ll>(n + 1, -1));
  dpBracket.resize(n + 1, vector<ll>(n + 1, -1));
  dpLeft.resize(n + 1, vector<ll>(n + 1, -1));
  dpRight.resize(n + 1, vector<ll>(n + 1, -1));

  preStarts.resize(n + 2, 0);
  for (int i = 1; i <= n; i++) {
    if (IsStart(i)) {
      preStarts[i] = preStarts[i - 1] + 1;
    }
  }

  sufStarts.resize(n + 2, 0);
  for (int i = n; i >= 1; i--) {
    if (IsStart(i)) {
      sufStarts[i] = sufStarts[i + 1] + 1;
    }
  }
}
void Solver() {  //
  scanf("%d%d", &n, &k);
  scanf("%s", str + 1);
  Init();
  printf("%lld\n", Dfs(1, n));
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