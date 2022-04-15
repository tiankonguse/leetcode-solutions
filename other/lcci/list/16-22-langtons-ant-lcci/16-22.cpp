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

// right(0) down(1) left(2) up(3)
int dir4[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
class Solution {
  map<pair<int, int>, char> m;

  void Step(int K) {
    int d = 0;
    int x = 0, y = 0;
    d = 0;

    // x,y 储存的是下个方向的位置

    while (K--) {
      pair<int, int> p = {x, y};
      if (m.count(p) == 0) {
        m[p] = '_';
      }

      char& c = m[p];

      if (c == '_') {
        d = (d + 1) % 4;
        c = 'X';
      } else {
        d = (d + 3) % 4;
        c = '_';
      }

      x += dir4[d][0];
      y += dir4[d][1];
    }

    m[{x, y}] = "RDLU"[d];
  }

  vector<string> ans;

  void Solver() {
    int minX = 0, minY = 0, maxX = 0, maxY = 0;
    for (auto [p, c] : m) {
      auto [x, y] = p;
      minX = min(minX, x);
      maxX = max(minX, x);
      minY = min(minY, y);
      maxY = max(maxY, y);
    }

    int row = maxY - minY + 1;
    int col = maxX - minX + 1;

    ans.resize(row, string(col, '_'));

    for (auto [p, c] : m) {
      auto [x, y] = p;
      int Y = maxY - y;
      int X = x - minX;
      ans[Y][X] = c;
    }
  }

 public:
  vector<string> printKMoves(int K) {
    Step(K);
    Solver();
    return ans;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
