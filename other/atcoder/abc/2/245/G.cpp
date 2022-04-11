#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;

typedef long double ld;
typedef vector<ld> vld;

typedef vector<bool> vb;
// const int mod = 1e9 + 7;

#define FOR(i, a, b) for (auto i = a; i < b; ++i)
#define FOR1(i, a, b) for (auto i = a; i <= b; ++i)
#define DWN(i, b, a) for (auto i = b - 1; i >= a; --i)
#define DWN1(i, b, a) for (auto i = b; i >= a; --i)

#define rep(i, n) for (ll i = 0; i < (n); i++)
#define rep1(i, n) for (ll i = 1; i <= (n); i++)
#define rrep(i, n) for (ll i = (n)-1; i >= 0; i--)
#define rrep1(i, n) for (ll i = (n); i >= 1; i--)
#define all(v) (v).begin(), (v).end()

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;

template <class T>
using max_queue = priority_queue<T>;

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

template <class T>
void chmin(T& a, T b) {
  a = min(a, b);
}
template <class T>
void chmax(T& a, T b) {
  a = max(a, b);
}

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;
constexpr ld EPS = 1e-12;
ld PI = acos(-1.0);

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

/*

lower_bound 大于等于
upper_bound 大于

vector / array : upper_bound(vec.begin(), vec.end(), v)
map: m.upper_bound(v)

区间 [l,r]内满足的个数：
upper_bound(vec.begin(), vec.end(), r) - lower_bound(vec.begin(), vec.end(), l);
std::distance(v.begin(), it)
map/set distance 复杂度 O(N)
vector/数组 distance 复杂度 O(1)

vector预先分配内存 reserve
反转 reverse(v.begin(), v.end())


sum = accumulate(a.begin(), a.end(), 0ll);
unordered_map / unordered_set

__builtin_popcount 一的个数

size_t found=str.find(string/char/char*);
std::string::npos

排序，小于是升序：[](auto&a, auto&b){ return a < b; })
优先队列 priority_queue<Node>：top/pop/push/empty
struct Node {
  Node(int t = 0) : t(t) {}
  int t;
  // 小于是最大堆，大于是最小堆
  bool operator<(const Node& that) const { return this->t < that.t; }
};

mutex mtx;       // 互斥量，锁，定义一个即可
condition_variable cv; // 条件变量
cv.notify_one(); // 事件通知
unique_lock<mutex> lck(mtx);
cv.wait(lck); //等待事件

atomic_int tick; // 原子计数
this_thread::yield();  // 线程 sleep

#include <semaphore.h> // 需要手动包含信号量头文件
sem_t sem_done;
sem_init(&bar_done, 0 , 1);
sem_wait(&bar_done);
sem_post(&foo_done);

*/

ll N, M, K, L;
vll A, B;
vvpll g;     // <Person, Cost>
vvpll flag;  // <cost, Nation>

ll FindNation(ll u, ll nation) {
  ll pos = -1;
  rep(i, flag[u].size()) {
    auto [flagCost, flagNation] = flag[u][i];
    if (flagNation == nation) {
      pos = i;
      break;
    }
  }
  return pos;
}

void FixNation(ll u) {
  auto& flagu = flag[u];
  for (int i = flagu.size() - 1; i > 0; i--) {
    if (flagu[i].first < flagu[i - 1].first) {
      swap(flagu[i], flagu[i - 1]);
    }
  }
  while (flagu.size() > 2) {
    flagu.pop_back();
  }
}

void AddNation(ll u, ll cost, ll nation) {  //
  auto& flagu = flag[u];
  flagu.push_back({cost, nation});
  FixNation(u);
}

void Solver() {  //
  flag.resize(N, vpll(1, {INFL, -1}));

  min_queue<tuple<ll, ll, ll>> que;  // <cost, Person, Nation>
  for (auto u : B) {
    que.push({0, u, A[u]});
    AddNation(u, 0, A[u]);
  }

  while (!que.empty()) {
    auto [oldCost, u, nation] = que.top();
    que.pop();

    if (oldCost) {  // 起点是 0，不需要剪枝
      ll pos = FindNation(u, nation);
      if (pos == -1) {  // 非最优，被淘汰
        continue;
      } else {  // 有更优答案
        if (flag[u][pos].first < oldCost) {
          continue;
        }
      }
    }

    for (auto [v, c] : g[u]) {
      ll newCost = oldCost + c;

      // 先找相同的 Nation
      if (ll pos = FindNation(v, nation); pos != -1) {  // 已存在，看是否更优
        auto& [flagCost, flagNation] = flag[v][pos];
        if (flagCost > newCost) {
          flagCost = newCost;
          que.push({newCost, v, nation});
          FixNation(v);
        }
        continue;
      }

      if (flag[v].back().first > newCost) {  // 有更优答案
        que.push({newCost, v, nation});
        AddNation(v, newCost, nation);
      }
    }
  }
}

int main() {
  scanf("%lld%lld%lld%lld", &N, &M, &K, &L);
  A.resize(N);
  rep(i, N) {  //
    scanf("%lld", &A[i]);
  }

  B.resize(L);
  rep(i, L) {  //
    scanf("%lld", &B[i]);
    B[i]--;
  }

  g.resize(N);
  rep(i, M) {
    ll u, v, c;
    scanf("%lld%lld%lld", &u, &v, &c);
    u--;
    v--;
    g[u].push_back({v, c});
    g[v].push_back({u, c});
  }

  Solver();

  rep(u, N) {  //
    ll ans = -1;
    rep(i, flag[u].size()) {
      auto [flagCost, flagNation] = flag[u][i];
      if (flagNation != A[u]) {
        ans = flagCost;
        break;
      }
    }
    if (ans == INFL) {
      ans = -1;
    }
    printf("%lld%c", ans, u + 1 == N ? '\n' : ' ');
  }

  return 0;
}
