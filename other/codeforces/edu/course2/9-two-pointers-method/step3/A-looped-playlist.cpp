/*
ID: tiankonguse
TASK: A. Looped Playlist  A. 循环播放列表
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/A
PATH: ITMO Academy: pilot course » Two Pointers Method » Step 2 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/
*/
#define TASK "A-looped-playlist"
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

int n, n2;
ll p;
vector<ll> nums;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d%lld", &n, &p);
  n2 = n * 2;
  nums.resize(n2 + 1);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &nums[i]);
  }
  for (int i = n + 1; i <= n2; i++) {
    nums[i] = nums[i - n];
  }
}

ll ansIndex = 0;
ll ansNum = 0;
void SolverEx() {
  ll sum = 0;
  for (auto v : nums) {
    sum += v;
  }
  sum /= 2;
  ll fullNum = 0;
  if (p >= sum) {
    fullNum = p / sum;
    p = p % sum;
  }
  // printf("p=%lld fullNum=%lld n=%d\n", p, fullNum, n);
  if (p == 0) {
    ansIndex = 1;
    ansNum = fullNum * n;
    return;
  }

  ansIndex = -1;
  ansNum = n + 1;

  int r = 1;
  sum = 0;
  for (int l = 1; l <= n; l++) {  //[l, r)
    while (r <= n2 && sum < p) {
      sum += nums[r];
      r++;
    }
    if (sum < p) break;
    if (ansNum > r - l) {
      ansNum = r - l;
      ansIndex = l;
    }
    sum -= nums[l];
  }
  if (ansIndex == -1) {
    ansIndex = 1;
    ansNum = n;
  }
  ansNum += fullNum * n;
}

void Solver() {  //
  SolverEx();
  printf("%lld %lld\n", ansIndex, ansNum);
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