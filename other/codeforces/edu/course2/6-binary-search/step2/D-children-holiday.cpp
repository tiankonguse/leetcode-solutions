/*
ID: tiankonguse
TASK: D. Children Holiday  D. 儿童假期
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/D
PATH: ITMO Academy: pilot course » Binary Search » Step 2 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
*/
#define TASK "D-children-holiday"
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

ll n, m;
vector<tuple<ll, ll, ll>> nums;
vector<ll> paths;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo.out", "w", stdout);
#endif
  scanf("%lld%lld", &n, &m);
  nums.reserve(m);
  for (int i = 0; i < m; i++) {
    ll t, y, z;
    scanf("%lld%lld%lld", &t, &z, &y);
    nums.push_back({t, z, y});
  }
  paths.resize(m, 0);
}

bool Check(ll T) {
  ll num = 0;
  for (int i = 0; i < m; i++) {
    auto [t, z, y] = nums[i];
    ll loopTime = (t * z + y);
    ll loopNum = T / loopTime;
    ll leftTime = T % loopTime;

    paths[i] = 0;
    paths[i] += loopNum * z;  // 周期内可以充的气球个数
    if (leftTime >= t * z) {
      paths[i] += z;  // 没有休息时间，但是可以把 z 个气球都重启
    } else {
      paths[i] += leftTime / t;
    }
    num += paths[i];
  }
  return num >= n;
}

ll Search() {
  if (n == 0) return 0;
  ll l = 0, r = n * 200 + 1;  // 假设每周期只充1个气球，最大周期是 200
  while (l < r) {             // [l,r)
    ll m = (l + r) / 2;
    if (Check(m)) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  Check(r);  // 最后一次再计算答案
  ll leftNum = n;
  for (auto& v : paths) {  // 气球可能多了，删除多余的气球
    if (v > leftNum) {
      v = leftNum;
      leftNum = 0;
    } else {
      leftNum -= v;
    }
  }
  return r;
}
void Solver() {  //
  // printf("%s\n", to_string(Search()).data());
  printf("%lld\n", Search());
  for (int i = 0; i < m; i++) {
    printf("%lld%c", paths[i], i + 1 == m ? '\n' : ' ');
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