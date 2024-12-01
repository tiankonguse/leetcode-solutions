/*
ID: tiankonguse
TASK: milk4
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "milk4"
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

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

int Q, P;
vector<int> nums;

void Fitle() {
  vector<int> numsEx;
  numsEx.reserve(P);
  for (auto a : nums) {
    bool ok = true;
    for (auto b : numsEx) {
      if (a % b == 0) {
        ok = false;
        break;
      }
    }
    if (ok) {
      numsEx.push_back(a);
    }
  }
  nums.swap(numsEx);
  P = nums.size();
}

vector<int> ans;

vector<int> dp;
bool Check() {
  dp.clear();
  dp.resize(Q + 1, 0);
  dp[0] = 1;
  for (int i = 0; i <= Q; i++) {
    if (dp[i] == 0) continue;
    for (auto v : ans) {
      int V = v + i;
      if (V > Q) continue;
      if (V == Q) return true;
      dp[V] = 1;
    }
  }
  return false;
}

bool DfsSelect(int n, int pos) {
  if (n == 0) {
    return Check();
  }
  // 选择 pos
  ans.push_back(nums[pos]);
  if (DfsSelect(n - 1, pos + 1)) {
    return true;
  }
  ans.pop_back();

  // 不选择 pos
  if (pos + n < P) {
    return DfsSelect(n, pos + 1);
  }
  return false;
}

void SolverEx() {
  //   printf("nums: ");
  //   for (auto v : nums) {
  //     printf(" %d", v);
  //   }
  //   printf("\n");
  for (int i = 1; i <= P; i++) {  // 枚举个数，预计不超过5个
    if (DfsSelect(i, 0)) {
      break;
    }
  }
}
void Solver() {  //
  scanf("%d%d", &Q, &P);
  nums.resize(P);
  for (int i = 0; i < P; i++) {
    scanf("%d", &nums[i]);
  }
  sort(nums.begin(), nums.end());
  Fitle();
  SolverEx();
  printf("%d", int(ans.size()));
  for (auto v : ans) {
    printf(" %d", v);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*
------ Data for Run 3 [length=13 bytes] ------
59
3
7
11
13
----- our output ---------
2_7_13
--------------------------
*/