/*
ID: tiankonguse
TASK: A. K-th Number in the Union of Segments A. 线段并集中的第 K 个数
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/6/5/practice/contest/285084/problem/A
PATH: ITMO Academy: pilot course » Binary Search » Step 3 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
*/
#define TASK "A-k-th-number-in-the-union-of-segments"
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

ll n, k;
vector<pair<ll, ll>> nums;

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen("demo.out", "w", stdout);
#endif
  scanf("%lld%lld", &n, &k);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld%lld", &nums[i].first, &nums[i].second);
  }
  k++;
}

void InitData() {}

//  Probably, the solution is executed with error 'signed integer overflow' on the line 97
// 转化为整形，会越界
const ll A = 1e9;
const ll N = 1e5;

bool Check(ll V) {  //
  ll num = 0;       // 小于 V 的个数
  for (auto [l, r] : nums) {
    r = min(r, V);
    if (r >= l) {
      num += r - l + 1;
    }
  }
  return num >= k;  // 从 1 开始
}

ll Search() {
  ll l = -2 * A, r = 2 * A;
  while (l < r) {  // [l,r)
    auto m = l + (r - l + 1) / 2 - 1;
    // printf("m=%lld l=%lld, r=%lld\n", m, l, r);
    if (Check(m)) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  return r;
}
void Solver() {  //
  InitData();
  printf("%lld\n", Search());
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