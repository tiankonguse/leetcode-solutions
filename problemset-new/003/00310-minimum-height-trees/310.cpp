#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef __int128_t int128;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<pll> vpll;

typedef long double ld;
typedef vector<ld> vld;

typedef vector<bool> vb;
typedef vector<string> vs;

// const int mod = 1e9 + 7;

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
unordered_map / unordered_set

lower_bound 大于等于
upper_bound 大于
reserve 预先分配内存
reverse(all(vec)) 反转
sum = accumulate(a.begin(), a.end(), 0ll);
__builtin_popcount 一的个数
vector / array : upper_bound(all(vec), v)
map: m.upper_bound(v)

区间个数： std::distance(v.begin(), it)
map/set distance 复杂度 O(N)
vector/数组 distance 复杂度 O(1)



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
*/

class Solution {
  vector<vector<int>> g;
  vi pre, h;
  map<int, vector<int>> m;  // 各树高的答案

  int dfs(int u, int p) {
    int h0 = 0;
    pre[u] = p;
    for (auto v : g[u]) {
      if (v == p) continue;
      h0 = max(h0, 1 + dfs(v, u));
    }
    h[u] = h0;
    printf("u=%d p=%d h0=%d\n", u, p, h0, );
    return h0;
  }

  void Solver(int u, int p, int ph) {
    int hu = ph + 1;

    map<int, int> hs;
    hs[ph + 1]++;
    for (auto v : g[u]) {
      if (v == p) continue;
      hu = max(hu, 1 + h[v]);
      hs[1 + h[v]]++;
    }
    m[hu].push_back(u);

    for (auto v : g[u]) {
      if (v == p) continue;
      int hv = 1 + h[v];
      hs[hv]--;
      if (hs[hv] == 0) hs.erase(hv);

      if (hs.empty()) {
        Solver(v, u, ph + 1);
      } else {
        Solver(v, u, hs.rbegin()->first);
      }

      hs[hv]++;
    }
  }

 public:
  vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    if (n == 2) return {0, 1};
    g.resize(n);
    pre.resize(n);
    h.resize(n);
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      g[u].push_back(v);
      g[v].push_back(u);
    }
    dfs(0, -1);  // 以 0 为根建树
    Solver(0, -1, -1);
    return m.begin()->second;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
