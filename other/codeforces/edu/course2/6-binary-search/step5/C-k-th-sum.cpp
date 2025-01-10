/*
ID: tiankonguse
TASK: C. K-th Sum  C. K 次和
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/6/5/practice/contest/285084/problem/C
PATH: ITMO Academy: pilot course » Binary Search » Step 3 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
*/
#define TASK "C-k-th-sum"
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
vector<vector<ll>> nums;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen("demo.out", "w", stdout);
#endif
  scanf("%lld%lld", &n, &k);
  nums.resize(2, vector<ll>(n));
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%lld", &nums[i][j]);
    }
  }
}

void InitData() {
  for (int i = 0; i < 2; i++) {
    sort(nums[i].begin(), nums[i].end());
  }
}

//  Probably, the solution is executed with error 'signed integer overflow' on the line 97
// 转化为整形，会越界
const ll N9 = 1e9;

bool Check(const ll V) {  //
  ll num = 0;             // 小于 V 的个数
  auto& A = nums[1];
  for (auto v : nums[0]) {
    num += upper_bound(A.begin(), A.end(), V - v) - A.begin();
  }
  return num >= k;  // 从 1 开始
}
/*
 1  2  3  4  5
 2  4  6  8 10
 3  6  9 12 15
 4  8 12 16 20
 5 10 15 20 25
*/

ll Search() {
  ll l = 1, r = 2 * N9;
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