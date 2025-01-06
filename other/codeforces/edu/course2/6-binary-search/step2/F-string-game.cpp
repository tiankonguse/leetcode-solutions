/*
ID: tiankonguse
TASK: F. String Game  F. 弦乐游戏
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/F
PATH: ITMO Academy: pilot course » Binary Search » Step 2 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
*/
#define TASK "F-string-game"
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

const int N = 2e5 + 2;
char p[N], t[N];
vector<ll> nums;
vector<ll> flag;
int pn, tn;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo.out", "w", stdout);
#endif
  scanf("%s%s", p, t);
  pn = strlen(p);
  tn = strlen(t);
  nums.resize(pn);
  for (int pi = 0; pi < pn; pi++) {
    scanf("%lld", &nums[pi]);
  }
  flag.resize(pn, 0);
}

ll checkIndex = 0;
bool Check(ll x) {  //
  checkIndex++;
  for (int i = 0; i < x; i++) {
    flag[nums[i] - 1] = checkIndex;
  }
  int ti = 0;
  for (int pi = 0; pi < pn && ti < tn; pi++) {
    if (flag[pi] == checkIndex) continue;
    if (p[pi] == t[ti]) ti++;
  }
  return ti == tn;
}

ll Search() {
  ll l = 0, r = pn;
  while (l < r) {  // [l,r)
    auto m = (l + r) / 2;
    if (Check(m)) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  return r - 1;
}
void Solver() {  //
  // printf("%s\n", to_string(Search()).data());
  printf("%ld\n", Search());
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