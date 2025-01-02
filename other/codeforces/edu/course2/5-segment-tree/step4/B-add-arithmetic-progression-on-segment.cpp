/*
ID: tiankonguse
TASK: B. Add Arithmetic Progression On Segment B. 在段上添加算术级数
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/B
PATH: ITMO 学院：试点课程 » 线段树，第 2 部分 » 步骤2 » 实践
submission:
https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
*/
#define TASK "B-add-arithmetic-progression-on-segment"
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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod_10_9_7 = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

/*
线段树：区间修改，区间查询

输入数组： vector<int> str; [0, n-1]

SegTree segTree;
segTree.Init(str); // 内部会对数组进行右移，转化为 [1,n]
segTree.Build();
segTree.Update(l, r, val); // 区间 [l,r] 都加上 val, 数据范围 [1,n]
segTree.QueryMax/QueryMin/QuerySum 区间查询, 数据范围 [1,n]
*/

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
struct SegTree {
  vector<ll> flag;
  vector<pair<ll, ll>> sign;

  void Init(int n) {
    maxNM = n + 1;
    flag.resize(maxNM << 2, 0);
    sign.resize(maxNM << 2);
  }

  void UpdateNode(int rt, int l, int r, ll a, ll d) {
    flag[rt] = 1;
    sign[rt].first += a;
    sign[rt].second += d;
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
  }
  void PushDown(int rt, int l, int r) {
    if (flag[rt] == 0) return;

    int m = (l + r) >> 1;
    UpdateNode(rt << 1, l, m, sign[rt].first, sign[rt].second);
    UpdateNode(rt << 1 | 1, m + 1, r, sign[rt].first, sign[rt].second);
    flag[rt] = 0;
    sign[rt] = {0, 0};
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }
  void Update(int L, int R, ll a, ll d, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      UpdateNode(rt, l, r, a, d);
      return;
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, a, d, lson);
    if (R > m) Update(L, R, a, d, rson);
    PushUp(rt, l, r);
  }
  pair<ll, ll> Query(int L, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= L) {
      return sign[rt];
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    if (L <= m) {
      return Query(L, l, m, rt << 1);
    } else {
      return Query(L, m + 1, r, rt << 1 | 1);
    }
  }
};

int n, m;
void InitIO() {
  #ifdef USACO_LOCAL_JUDGE
    freopen("demo.in", "r", stdin);
    freopen("demo.out", "w", stdout);
  #endif
  scanf("%d%d", &n, &m);
}

string to_string(__int128_t ans) {
  string s;
  while (ans) {
    s.push_back('0' + (ans % 10));
    ans /= 10;
  }
  std::reverse(s.begin(), s.end());
  if (s.empty()) {
    s.push_back('0');
  }
  return s;
}

SegTree segTree;
void Solver() {  //
  segTree.Init(n);
  segTree.Build();
  while (m--) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int l, r;
      ll a, d;
      scanf("%d%d%lld%lld", &l, &r, &a, &d);
      segTree.Update(l, r, a - d * l, d);
    } else {
      int l;
      scanf("%d", &l);
      auto [a, b] = segTree.Query(l);
      // __int128_t A = a;
      // __int128_t B = b;
      // __int128_t L = l;
      // printf("%s\n", to_string(A + B * L).data());
      printf("%lld\n", a + b * l);
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
  // ll a = mod_10_9_7;
  // printf("a=%lld\n", a * a);
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/