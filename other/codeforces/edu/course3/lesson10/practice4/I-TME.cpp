/*
ID: tiankonguse
TASK: I、添加、总结
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/3/lesson/10/4/practice/contest/324369/problem/I
PATH: 社区课程 » 前缀和与差数组 » 步骤4 » 实践
submission:
*/
#define TASK "demo"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

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

void InitIO() {  //
}

typedef unsigned int ui;
ll M = 1LL << 32;
ll A, B;
ui a, b;
ui cur = 0;
inline ui nextRand() {
  cur = cur * a + b;
  return cur >> 8;
}

const int N = 1 << 24;
ui preSums[N + 1] = {0};

class TreeArrayEx {
 public:
  void Init(int n_) {
    n = n_ + 1;
    t1.clear();
    t1.resize(n + 10, 0);
    t2.clear();
    t2.resize(n + 10, 0);
  }

  inline void AddEx(int l, int r, ll v) {
    Add(l, v);
    Add(r + 1, -v);  // 将区间加差分为两个前缀加
  }

  inline ll Query(int l, int r) {
    return (r + 1ll) * Query(t1, r) - 1ll * l * Query(t1, l - 1) -
           (Query(t2, r) - Query(t2, l - 1));
  }

 private:
  inline void Add(int k, ll v) {
    ll v1 = k * v;
    while (k <= n) {
      t1[k] += v, t2[k] += v1;
      k += Lowbit(k);
    }
  }
  inline ll Query(vector<ll>& t, int k) {
    ll ret = 0;
    while (k) {
      ret += t[k];
      k -= Lowbit(k);
    }
    return ret;
  }
  inline int Lowbit(int x) { return x & -x; }
  vector<ll> t1, t2;
  int n;
};

TreeArrayEx treeArray;

void Solver() {  //
  int m, q;
  scanf("%d%d%lld%lld", &m, &q, &A, &B);
  a = A;
  b = B;
  treeArray.Init(N);

  while (m--) {
    ui adding = nextRand();
    ui l = nextRand();
    ui r = nextRand();
    if (l > r) swap(l, r);
    l++, r++;
    treeArray.AddEx(l, r, adding);
  }

  ll ans = 0;
  while (q--) {
    ui l = nextRand();
    ui r = nextRand();
    if (l > r) swap(l, r);
    l++, r++;
    ans = (ans + treeArray.Query(l, r)) % M;
  }

  printf("%lld\n", ans);
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my =
      std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(
          t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
}

int main(int argc, char** argv) {
  InitIO();
  ExSolver();
  return 0;
}

/*

*/