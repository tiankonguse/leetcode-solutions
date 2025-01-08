/*
ID: tiankonguse
TASK: A. Maximum Average Segment A. 最大平均段
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/6/4/practice/contest/285069/problem/A
PATH: ITMO Academy: pilot course » Binary Search » Step 4 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
*/
#define TASK "A-maximum-average-segment"
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

ll n, d;
vector<ll> nums;

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo.out", "w", stdout);
#endif
  scanf("%lld%lld", &n, &d);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
  }
}

void InitData() {}

//  Probably, the solution is executed with error 'signed integer overflow' on the line 97
// 转化为整形，会越界
const ll A = 1e9;
const ll N = 1e5;
vector<ll> paths;

vector<ll> preFlag;
int ansL, ansR;
bool debugFlag = 0;
bool Eq(double a, double b) { return (a - eps <= b && b <= a + eps); }
bool Check(double avg) {  //
  double preMinSum = INT_MAX;
  vector<double> preSum(n + 1, 0);
  int L = 0, R = 0;
  for (double v : nums) {
    v -= avg;
    R++;
    preSum[R] = preSum[R - 1] + v;
    // if (debugFlag) {
    //   printf("avg=%lf R=%d preSum=%lf preMinSum=%lf\n", avg, R, preSum[R], preMinSum);
    // }
    int P = R - d;
    if (P >= 0 && preSum[P] + eps < preMinSum) {
      preMinSum = preSum[P];
      L = P;
    }

    if (R - L >= d && (preMinSum + eps <= preSum[R] || Eq(preMinSum, preSum[R]))) {
      ansL = L + 1;
      ansR = R;
      return true;
    }
  }

  return false;
}

void Search() {
  // if (d == n) {
  //   ansL = 1;
  //   ansR = n;
  //   return;
  // }
  double l = 0, r = N + 1;
  while (l + eps < r) {  // [l,r)
    auto m = (l + r) / 2;
    if (Check(m)) {
      // printf("m=%lf l=%d r=%d dis=%d\n", m, ansL, ansR, ansR - ansL + 1);
      l = m + eps;
    } else {
      // printf("m=%lf \n", m);
      r = m;
    }
  }
  if (r <= eps) {
    // printf("r<=eps \n");
    r = 0;
    Check(r);
  } else {
    Check(r - eps);
  }
  // debugFlag = 1;
  // Check(6.6);
  // debugFlag = 0;
}
void Solver() {  //
  InitData();
  Search();
  printf("%d %d\n", ansL, ansR);
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