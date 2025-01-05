/*
ID: tiankonguse
TASK: F. Mountain  F.山
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/F
https://www.luogu.com.cn/problem/P5848
PATH: ITMO 学院：试点课程 » 线段树，第 2 部分 » 步骤4 » 实践
submission:
https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/edu
DESC:
*/
#define TASK "F-mountain-v1"
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

unordered_map<ll, int> H;
vector<ll> RH;
int Hindex;  // [1, Hindex]
int n;
void Hadd(int a) {
  if (a >= 0 && a <= n) {
    H[a] = 0;
  }
}

struct SegTree {
  vector<ll> sign;
  vector<ll> addVal;
  vector<ll> disVal;
  vector<ll> maxVal;

  void Init(int n) {
    maxNM = n + 1;
    sign.resize(maxNM << 2, 0);
    addVal.resize(maxNM << 2, 0);
    disVal.resize(maxNM << 2, 0);
    maxVal.resize(maxNM << 2, 0);
  }

  void UpdateNode(int rt, int l, int r, const ll& add) {
    sign[rt] = 1;
    addVal[rt] = add;
    disVal[rt] = add * (RH[r] - RH[l - 1]);  // 离散化时，需要使用离散化的上一个坐标，否则中间会少计算答案
    maxVal[rt] = max(add, disVal[rt]);       // 上升时，右边最大，下降时，左边最大
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {  //
    disVal[rt] = disVal[rt << 1] + disVal[rt << 1 | 1];
    maxVal[rt] = max(maxVal[rt << 1], disVal[rt << 1] + maxVal[rt << 1 | 1]);
  }
  void PushDown(int rt, int l, int r) {
    if (sign[rt] == 0) return;

    int m = (l + r) >> 1;
    UpdateNode(rt << 1, l, m, addVal[rt]);
    UpdateNode(rt << 1 | 1, m + 1, r, addVal[rt]);

    addVal[rt] = 0;
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
  void Update(int L, int R, const ll& add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      UpdateNode(rt, l, r, add);
      return;
    }
    PushDown(rt, l, r);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
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
      return disVal[rt << 1] + QueryMax(L, R, rson);
    } else {
      return max(QueryMax(L, R, lson), disVal[rt << 1] + QueryMax(L, R, rson));
    }
  }
};

const int N = 1e5;
struct Cmd {
  char op[2];
  int a, b;
  ll d, h;
  bool Read() {
    scanf("%s", op);
    if (op[0] == 'E') return false;
    if (op[0] == 'I') {
      scanf("%d%d%lld", &a, &b, &d);
    } else {
      scanf("%lld", &h);
    }
    return true;
  }
};
vector<Cmd> cmds;

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  freopen("demo-v1.out", "w", stdout);
#endif
  scanf("%d", &n);
  cmds.reserve(N);
  cmds.push_back({});
  while (cmds.back().Read()) {
    cmds.push_back({});
  }
  cmds.pop_back();
}

SegTree segTree;

ll Search(ll h) {
  MyPrintf("Search h=%lld val[n]=%lld\n", h, segTree.QueryMax(H[1], H[n]));
  // if (h == 0) return 0;
  if (segTree.QueryMax(H[1], H[n]) < h) return n;
  if (segTree.QueryMax(H[1], H[1]) >= h) return 0;
  int l = 1, r = Hindex;  //[l, r)
  while (l < r) {
    int mid = (l + r) / 2;
    if (segTree.QueryMax(1, mid) < h) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  MyPrintf(">=h r=%d\n", r);
  if (segTree.QueryMax(r, r) == h) {
    return RH[r] - 1;  //  最后一个不可达的位置，上个位置是答案
  }

  const int L = RH[r - 1];
  const int R = RH[r];
  const ll LH = segTree.QueryMax(r - 1, r - 1);
  const ll RH = segTree.QueryMax(r, r);
  MyPrintf("L=%d R=%d LH=%lld RH=%lld\n", L, R, LH, RH);

  // L->R, d = (RH - LH)/ (R - L)
  int LL = L, RR = R;
  auto CalMH = [RH, LH, R, L](ll M) -> ll {  //
    return LH + (M - L) * (RH - LH) / (R - L);
  };
  while (LL < RR) {
    ll M = (LL + RR) / 2;
    ll MH = CalMH(M);  // 肯定可以整除
    if (MH < h) {
      LL = M + 1;
    } else {
      RR = M;
    }
  }
  MyPrintf("RR=%d\n", RR);

  return RR - 1;
}

void Discretization() {
  Hadd(1);
  Hadd(n);
  for (auto& cmd : cmds) {
    if (cmd.op[0] == 'I') {
      Hadd(cmd.a - 1);
      Hadd(cmd.a);
      Hadd(cmd.b);
      Hadd(cmd.b + 1);
    }
  }
  map<ll, int> HH;
  for (auto [k, v] : H) {
    HH[k] = 0;
  }
  Hindex = 0;
  for (auto& [k, v] : HH) {
    v = ++Hindex;
    H[k] = v;
    MyPrintf("H v=%lld -> index=%d\n", k, v);
  }

  RH.resize(Hindex + 2);
  for (auto [k, v] : H) {
    RH[v] = k;
    MyPrintf("RH index=%d -> val=%lld\n", v, k);
  }
}

void Solver() {  //
  Discretization();

  segTree.Init(Hindex);
  segTree.Build();

  for (auto& cmd : cmds) {
    MyPrintf("op=%s\n", cmd.op);
    if (cmd.op[0] == 'I') {
      ll a = cmd.a;
      ll b = cmd.b;
      ll d = cmd.d;
      MyPrintf("[%lld,%lld] d=%lld\n", a, b, d);
      MyPrintf("H [%d,%d] d=%lld\n", H[a], H[b], d);
      segTree.Update(H[a], H[b], d);  // [a,b] 连续增加 d
    } else {
      ll h = cmd.h;
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
12
I 9 11 964
I 2 9 131
I 7 8 493
I 4 4 383
Q 821
I 7 9 268
Q 821
I 11 12 906
Q 916
I 3 4 578
Q 476
I 1 6 212
Q 965
E


*/