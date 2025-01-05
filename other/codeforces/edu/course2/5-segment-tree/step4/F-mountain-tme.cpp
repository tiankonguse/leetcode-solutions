/*
ID: tiankonguse
TASK: F. Mountain  F.山
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/F
PATH: ITMO 学院：试点课程 » 线段树，第 2 部分 » 步骤4 » 实践
submission:
https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
DESC: 元素个数 1e9, 线段树大小 4e9，爆了
*/
#define TASK "F-mountain-tme"
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

int maxNM;

typedef long long ll;

struct SegTree {
  vector<ll> sign;
  vector<ll> opVal;
  vector<ll> addVal;
  vector<ll> mulVal;
  vector<ll> maxVal;

  void Init(int n) {
    maxNM = n + 1;
    sign.resize(maxNM << 2, 0);
    opVal.resize(maxNM << 2, 0);
    addVal.resize(maxNM << 2, 0);
    mulVal.resize(maxNM << 2, 0);
    maxVal.resize(maxNM << 2, 0);
  }

  void UpdateNode(int rt, int l, int r, int op, const ll& add, const ll& mul) {
    sign[rt] = 1;

    if (op == 1) {
      opVal[rt] = op;
      addVal[rt] = add;
      mulVal[rt] = mul;
      maxVal[rt] = addVal[rt] + max(mulVal[rt] * l, mulVal[rt] * r);
    } else {  // add 只会增加 add
      if (opVal[rt] == 0) {
        opVal[rt] = op;
      }
      addVal[rt] += add;
      maxVal[rt] += add;
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
    maxVal[rt] = max(maxVal[rt << 1], maxVal[rt << 1 | 1]);
  }
  void PushDown(int rt, int l, int r) {
    if (sign[rt] == 0) return;
    int m = (l + r) >> 1;
    UpdateNode(rt << 1, l, m, opVal[rt], addVal[rt], mulVal[rt]);
    UpdateNode(rt << 1 | 1, m + 1, r, opVal[rt], addVal[rt], mulVal[rt]);
    addVal[rt] = 0;
    mulVal[rt] = 0;
    opVal[rt] = 0;
    sign[rt] = 0;
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
  void Update(int L, int R, int op, const ll& add, const ll& mul, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      UpdateNode(rt, l, r, op, add, mul);
      return;
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, op, add, mul, lson);
    if (R > m) Update(L, R, op, add, mul, rson);
    PushUp(rt, l, r);
  }
  ll QueryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxVal[rt];
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    if (R <= m) {
      return QueryMax(L, R, lson);
    } else if (L > m) {
      return QueryMax(L, R, rson);
    } else {
      return max(QueryMax(L, R, lson), QueryMax(L, R, rson));
    }
  }
};

int n;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo-tme.out", "w", stdout);
#endif
  scanf("%d", &n);
}

SegTree segTree;

ll Search(ll h) {
  if (segTree.QueryMax(1, n) < h) return n;
  if (segTree.QueryMax(1, 1) >= h) return 0;
  int l = 1, r = n;  //[l, r)
  while (l < r) {
    int mid = (l + r) / 2;
    if (segTree.QueryMax(1, mid) < h) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  return r - 1;
}

void Solver() {  //
  segTree.Init(n);
  segTree.Build();
  while (1) {
    char op[3];
    scanf("%s", op);
    if (op[0] == 'E') break;
    if (op[0] == 'I') {
      int a, b;
      ll d;
      scanf("%d%d%lld", &a, &b, &d);
      // printf("I %d %d %lld\n", a, b, d);
      // [a,b] +d
      ll pre = 0;
      if (a > 1) {
        pre = segTree.QueryMax(a - 1, a - 1);
      }
      const ll oldBVal = segTree.QueryMax(b, b);
      const ll add = pre - d * (a - 1);
      const ll mul = d;
      // printf("preVal=%lld\n", pre);
      // printf("[%d,%d] op=1 add=%lld mul=%lld\n", a, b, add, mul);
      segTree.Update(a, b, 1, add, mul);  // [a,b] 连续增加 d

      if (b < n) {
        const ll newBVal = segTree.QueryMax(b, b);
        if (oldBVal != newBVal) {
          // printf("[%d,%d] op=2 add=%lld\n", b + 1, n, newBVal - oldBVal);
          segTree.Update(b + 1, n, 2, newBVal - oldBVal, 0);  // [b+1, n] 平移升高
        }
      }
    } else {
      ll h;
      scanf("%lld", &h);
      printf("%lld\n", Search(h + 1));  //
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