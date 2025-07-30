/*
ID: tiankonguse
TASK: palin
LANG: C++
MAC EOF: ctrl+D
link:  https://www.luogu.com.cn/problem/P7915
PATH:
submission:
*/
#define TASK "palin"
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
#define TASKNO "2"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

int t;
int n, n2;
vector<int> nums;
vector<vector<int>> indexs;
map<tuple<int, int, int, int>, int> H;
string ans;

bool Check(int p1, int p2, int p3, int p4, int num) {  // (p1,p2), (p3,p4)
  if (num == n) {                                      // 找到一组答案
    return true;
  }
  // 尝试选择左端点
  if (p1 + 1 < p2) {
    ans.push_back('L');
    p1++;
    if (p2 - 1 > p1 && nums[p1] == nums[p2 - 1] && Check(p1, p2 - 1, p3, p4, num + 1)) {
      ans.push_back('L');
      return true;
    }
    if (p3 + 1 < p4 && nums[p1] == nums[p3 + 1] && Check(p1, p2, p3 + 1, p4, num + 1)) {
      ans.push_back('R');
      return true;
    }
    ans.pop_back();
    p1--;
  }
  // 尝试选择右端点
  if (p3 + 1 < p4) {
    ans.push_back('R');
    p4--;
    if (p2 - 1 > p1 && nums[p2 - 1] == nums[p4] && Check(p1, p2 - 1, p3, p4, num + 1)) {
      ans.push_back('L');
      return true;
    }
    if (p3 + 1 < p4 && nums[p3 + 1] == nums[p4] && Check(p1, p2, p3 + 1, p4, num + 1)) {
      ans.push_back('R');
      return true;
    }
    ans.pop_back();
    p4++;
  }
  return false;
}

bool Check() {  //
  int p1 = 0, p4 = n2 + 1, p2, p3;
  // 尝试左端点
  ans.push_back('L');
  p1++;
  p2 = p3 = indexs[nums[p1]].back();  // 选择左边的，另一个值在右边
  if (Check(p1, p2, p3, p4, 1)) {
    ans.push_back('L');
    return true;
  }
  ans.pop_back();
  p1--;

  // 尝试右端点
  ans.push_back('R');
  p4--;
  p2 = p3 = indexs[nums[p4]].front();  // 选择右边的，另一个值在左边
  if (Check(p1, p2, p3, p4, 1)) {
    ans.push_back('L');
    return true;
  }
  return false;
}

void Solver() {  //
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    indexs.clear();
    indexs.resize(n + 2);
    n2 = n * 2;
    nums.clear();
    nums.resize(n2 + 2, 0);
    for (int i = 1; i <= n2; i++) {
      scanf("%d", &nums[i]);
      indexs[nums[i]].push_back(i);
    }
    ans.clear();
    ans.reserve(n2);
    if (Check()) {
      printf("%s\n", ans.c_str());
    } else {
      printf("-1\n");
    }
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