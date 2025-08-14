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
#define TASKNO "3"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

int t;
int n, n2, nn;
vector<int> nums;
vector<vector<int>> indexs;
set<tuple<int, int, int, int>> H;
string ans;

// s 原始字符串; ss 预处理后的字符串;  p 各中心的半径
const int kStart = -1;
const int kSplit = -2;
vector<int> ss;
vector<int> p;
void Manacher(const int n, const vector<int>& s, vector<int>& ss, vector<int>& p) {
  //   int n = s.size();
  nn = n * 2 + 2;

  ss[0] = kStart;
  ss[nn - 1] = kSplit;
  for (int i = 0; i < n; i++) {
    ss[i * 2 + 1] = kSplit;
    ss[i * 2 + 2] = s[i];
  }
  int r = 0, id = 0;  // 到达最远 r 时，中心为 id, (id-r, id+r)
  for (int i = 1; i < nn; i++) {
    p[i] = 1;
    if (r > i) {
      p[i] = min(p[2 * id - i], r - i);
    }
    while (i + p[i] < nn && i - p[i] > 0 && ss[i + p[i]] == ss[i - p[i]]) {
      p[i]++;
    }
    if (i + p[i] > r) {
      r = i + p[i];
      id = i;
    }
  }
  //   for (int i = 0; i < n; i++) {
  //     printf("i=%d s=%d\n", i, s[i]);
  //   }
  //   for (int i = 0; i < nn; i++) {
  //     printf("i=%d ss=%d p=%d\n", i, ss[i], p[i]);
  //   }
}

// i -> 2*i+1
bool Check(int l, int r) {  // (l, r)
  l++, r--;
  assert(l < r);
  assert(r < n2);
  int L = l * 2 + 1, R = r * 2 + 1;
  assert(R < nn);
  int len = R - L + 1;
  int mid = (L + R) / 2;
  return p[mid] >= (len + 1) / 2;
}

bool Check(const int p1, const int p2, const int p3, const int p4, int num) {  // (p1,p2), (p3,p4)
  // const tuple<int, int, int, int> tup = make_tuple(p1, p2, p3, p4);
  // if (H.count(tup)) {
  //   return false;
  // }
  if (num == n) {  // 找到一组答案
    return true;
  }
  // // 只有一段时，必须是回文串
  // if (p1 + 1 == p2 && !Check(p3, p4)) {
  //   H.insert(tup);
  //   return false;
  // }
  // if (p3 + 1 == p4 && !Check(p1, p2)) {
  //   H.insert(tup);
  //   return false;
  // }

  // 尝试选择左端点
  if (p1 + 1 < p2 && p2 - 1 > p1 + 1 && nums[p1 + 1] == nums[p2 - 1]) {
    ans.push_back('L');
    if (Check(p1 + 1, p2 - 1, p3, p4, num + 1)) {
      ans.push_back('L');
      return true;
    } else {
      ans.pop_back();
      return false;
    }
  }
  if (p1 + 1 < p2 && p3 + 1 < p4 && nums[p1 + 1] == nums[p3 + 1]) {
    ans.push_back('L');
    if (Check(p1 + 1, p2, p3 + 1, p4, num + 1)) {
      ans.push_back('R');
      return true;
    } else {
      ans.pop_back();
      return false;
    }
  }
  // 尝试选择右端点
  if (p3 + 1 < p4 && p2 - 1 > p1 && nums[p2 - 1] == nums[p4 - 1]) {
    ans.push_back('R');
    if (Check(p1, p2 - 1, p3, p4 - 1, num + 1)) {
      ans.push_back('L');
      return true;
    } else {
      ans.pop_back();
      return false;
    }
  }
  if (p3 + 1 < p4 && p3 + 1 < p4 - 1 && nums[p3 + 1] == nums[p4 - 1]) {
    ans.push_back('R');
    if (Check(p1, p2, p3 + 1, p4 - 1, num + 1)) {
      ans.push_back('R');
      return true;
    } else {
      ans.pop_back();
      return false;
    }
  }

  return false;
}

bool Check() {  //
  int p1 = -1, p4 = n2, p2, p3;
  // 尝试左端点
  ans.push_back('L');
  p2 = p3 = indexs[nums[p1 + 1]].back();  // 选择左边的，另一个值在右边
  if (Check(p1 + 1, p2, p3, p4, 1)) {
    ans.push_back('L');
    return true;
  }
  ans.pop_back();

  // 尝试右端点
  ans.push_back('R');
  p2 = p3 = indexs[nums[p4 - 1]].front();  // 选择右边的，另一个值在左边
  if (Check(p1, p2, p3, p4 - 1, 1)) {
    ans.push_back('L');
    return true;
  }
  ans.pop_back();
  return false;
}

void Solver() {  //
  scanf("%d", &t);
  indexs.resize(max6);
  nums.resize(max6);
  ans.reserve(max6);
  // ss.resize(max6);
  // p.resize(max6);
  while (t--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      indexs[i].clear();
    }
    n2 = n * 2;
    for (int i = 0; i < n2; i++) {
      scanf("%d", &nums[i]);
      nums[i]--;
      indexs[nums[i]].push_back(i);
    }
    // Manacher(n2, nums, ss, p);
    ans.clear();
    ans.reserve(n2);
    H.clear();
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