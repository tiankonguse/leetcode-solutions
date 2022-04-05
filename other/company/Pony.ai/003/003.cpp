#include <bits/stdc++.h>

// #include "base.h"
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
 public:
  int minJump(vector<int>& jump) {
    int n = jump.size();

    return 0;
  }
};

map<pll, ll> m;
ll mapIndex = 0;

ll H(ll x, ll y) {
  pll p = {x, y};
  if (m.count(p) == 0) {
    // printf("H x=%lld y=%lld index=%lld\n", x, y, mapIndex);
    m[p] = mapIndex++;
  }
  return m[p];
}

// 0: UP, 1: RIGHT, 2:DOWN 3: LEFT

ll UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3, START = 4;

pll D(ll x1, ll y1, ll x2, ll y2) {
  if (x1 == x2) {
    if (y1 > y2) {
      return {y1 - y2, DOWN};
    } else {
      return {y2 - y1, UP};
    }
  } else {  // y1 == y2
    if (x1 < x2) {
      return {x2 - x1, RIGHT};
    } else {
      return {x1 - x2, LEFT};
    }
  }
}

struct Node {
  ll h, dir, dis;
};
vector<vector<Node>> g;
ll t1, t2, t3;
ll sum[3];

void Add(ll x1, ll y1, ll x2, ll y2) {
  ll h1 = H(x1, y1);
  ll h2 = H(x2, y2);
  auto [dis, dir] = D(x1, y1, x2, y2);
  // printf("%lld -> %lld dir=%lld dis=%lld\n", h1, h2, dir, dis);
  // printf("%lld -> %lld dir=%lld dis=%lld\n", h2, h1, (dir + 2) % 4, dis);
  g[h1].push_back(Node{h2, dir, dis});
  g[h2].push_back(Node{h1, (dir + 2) % 4, dis});
}

struct State {
  ll t, h, dir;
  bool operator<(const State& that) const { return this->t > that.t; }
};

ll NextDir(ll t) {
  t %= (t1 + t2 + t3);
  if (t < t1) {
    return 1;
  }
  if (t < t1 + t2) {
    return 2;
  }
  return 3;
}

bool Check(ll t, ll nowDir, ll nextDir) {
  ll deng = NextDir(t);
  if (nowDir == START) return true;
  if ((nowDir + 1) % 4 == nextDir) return true;               // 右转
  if (deng == 3 && nowDir == nextDir) return true;            // 直行
  if (deng == 2 && (nowDir + 3) % 4 == nextDir) return true;  // 左转
  return false;
}

ll NextTime(ll t, ll nowDir, ll nextDir) {
  while (!Check(t, nowDir, nextDir)) {
    ll offset = t % (t1 + t2 + t3);
    rep(i, 3) {
      if (offset < sum[i]) {
        t += sum[i] - offset;
        break;
      }
    }
  }

  return t;
}

ll Solver(ll source, ll target) {
  priority_queue<State> que;
  que.push({0, source, START});

  while (!que.empty()) {
    auto state = que.top();
    que.pop();
    ll t = state.t, h = state.h, dir = state.dir;
    if (h == target) return t;

    for (auto& node : g[h]) {
      // printf("h=%lld t=%lld mod=%lld dir=%lld nextDir=%lld newH=%lld\n", h,
      // t,
      //        t % sum[2], dir, node.dir, node.h);
      if (dir != START && (dir + 2) % 4 == node.dir) continue;  // 回头
      ll newT = NextTime(t, dir, node.dir) + node.dis;
      // printf("=> fixT=%lld dis=%lld nextH=%lld \n", newT, node.dis,
      // node.h);

      que.push({newT, node.h, node.dir});
    }
    g[h].clear();
  }
  return 0;
}

void Splity(map<ll, map<ll, ll>>& mx, map<ll, map<ll, ll>>& my) {
  for (auto& [x, xsegs] : mx) {
    for (auto [y1, y2] : xsegs) {
      auto ity = my.lower_bound(y1);
      while (ity != my.end() && ity->first <= y2) {
        ll y = ity->first;
        auto& ysegs = ity->second;

        auto itx = ysegs.upper_bound(x);
        if (itx != ysegs.begin()) {
          itx--;
          auto [x1, x2] = *itx;
          if (x1 < x && x < x2) {  // 可以拆分
            // printf("split: y=%lld x1=%lld x2=%lld x=%lld \n", y, x1, x2, x);
            ysegs[x1] = x;
            ysegs[x] = x2;
          }
        }

        ity++;
      }
    }
  }
}
void Splitx(map<ll, map<ll, ll>>& mx, map<ll, map<ll, ll>>& my) {
  for (auto& [y, ysegs] : my) {
    for (auto [x1, x2] : ysegs) {
      auto itx = mx.lower_bound(x1);
      while (itx != mx.end() && itx->first <= x2) {
        ll x = itx->first;
        auto& xsegs = itx->second;

        auto ity = xsegs.upper_bound(y);
        if (ity != xsegs.begin()) {
          ity--;
          auto [y1, y2] = *ity;
          if (y1 < y && y < y2) {
            // printf("split: x=%lld y1=%lld y2=%lld y=%lld \n", x, y1, y2, y);
            xsegs[y1] = y;
            xsegs[y] = y2;
          }
        }

        itx++;
      }
    }
  }
}

map<ll, map<ll, ll>> mx, my;

int InitGraph() {
  Splity(mx, my);
  Splitx(mx, my);

  ll num = 0;
  for (auto& [x, segs] : mx) {
    for (auto [y1, y2] : segs) {
      H(x, y1);
      H(x, y2);
    }
  }
  for (auto& [y, segs] : my) {
    for (auto [x1, x2] : segs) {
      H(x1, y);
      H(x2, y);
    }
  }

  g.resize(mapIndex);
  // printf("g size=%lld\n", num);
  for (auto& [x, segs] : mx) {
    for (auto [y1, y2] : segs) {
      Add(x, y1, x, y2);
    }
  }

  for (auto& [y, segs] : my) {
    for (auto [x1, x2] : segs) {
      Add(x1, y, x2, y);
    }
  }

  return 0;
}

void InitPoint(ll x, ll y) {
  if (mx.count(x) > 0) {
    auto& segs = mx[x];
    auto it = segs.upper_bound(y);
    if (it != segs.begin()) {
      it--;
      auto [y1, y2] = *it;
      if (y1 < y && y < y2) {
        segs[y1] = y;
        segs[y] = y2;
      }
    }
  }
  if (my.count(y) > 0) {
    auto& segs = my[y];
    auto it = segs.upper_bound(x);
    if (it != segs.begin()) {
      it--;
      auto [x1, x2] = *it;
      if (x1 < x && x < x2) {
        segs[x1] = x;
        segs[x] = x2;
      }
    }
  }
}

int main() {
  ll n;
  scanf("%lld", &n);
  ll x1, y1, x2, y2;
  rep(i, n) {
    scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
    if (y1 > y2) swap(y1, y2);
    if (x1 > x2) swap(x1, x2);
    if (x1 == x2) {
      mx[x1][y1] = y2;
    } else {
      my[y1][x1] = x2;
    }
  }

  scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
  scanf("%lld%lld%lld", &t1, &t2, &t3);
  sum[0] = t1;
  sum[1] = t1 + t2;
  sum[2] = t1 + t2 + t3;

  InitPoint(x1, y1);
  InitPoint(x2, y2);

  InitGraph();
  ll s = H(x1, y1), t = H(x2, y2);
  // printf("query [%lld]=>[%lld]\n", s, t);

  printf("%lld\n", Solver(s, t));
  return 0;
}
