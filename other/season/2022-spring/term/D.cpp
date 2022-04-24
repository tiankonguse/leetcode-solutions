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
// LONG_MIN, LONG_MAX

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

int shapes[8][6][10];

class Solution {
 public:
  vector<vector<int>> g;
  vector<vector<int>> shapes[8];
  vector<int> use;
  int n;

  vector<int> tmp;
  void Rotate(vector<int>& str) {
    tmp.clear();
    tmp.resize(n, 0);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        tmp[j] |= str[i] & (1 << j);
      }
    }
    str.swap(tmp);
  }

  void Reverse(vector<int>& str) {
    for (int& s : str) {
      int l = 0, r = n - 1;
      int tmp = 0;
      while (l < r) {
        int leftVal = 1 & (s >> l);
        int rightVal = 1 & (s >> r);
        tmp |= leftVal << r;
        tmp |= rightVal << l;
      }
      s = tmp;
    }
  }

  map<tuple<int, int, int>, set<tuple<int, int, int>>> h;

  void Add(tuple<int, int, int> a, tuple<int, int, int> b) {
    h[a].insert(b);
    // h[b].insert(a);
  }

  void Init() {
    for (int i = 0; i < n; i++) {  // p =0 上
      Add({0, 0, i}, {3, n - 1, i});
    }
    for (int i = 0; i < n; i++) {  // p =0 下
      Add({0, n - 1, i}, {1, 0, i});
    }
    for (int i = 0; i < n; i++) {  // p =0 左
      Add({0, i, 0}, {4, 0, i});
    }
    for (int i = 0; i < n; i++) {  // p =0 右
      Add({0, i, n - 1}, {5, 0, n - 1 - i});
    }

    for (int i = 0; i < n; i++) {  // p =1 上
      Add({1, 0, i}, {0, n - 1, i});
    }
    for (int i = 0; i < n; i++) {  // p =1 下
      Add({1, n - 1, i}, {2, 0, i});
    }
    for (int i = 0; i < n; i++) {  // p =1 左
      Add({1, i, 0}, {4, i, n - 1});
    }
    for (int i = 0; i < n; i++) {  // p =1 右
      Add({1, i, n - 1}, {5, i, 0});
    }

    for (int i = 0; i < n; i++) {  // p =2 上
      Add({2, 0, i}, {1, n - 1, i});
    }
    for (int i = 0; i < n; i++) {  // p =2 下
      Add({2, n - 1, i}, {3, 0, i});
    }
    for (int i = 0; i < n; i++) {  // p =2 左
      Add({2, i, 0}, {4, n - 1, n - 1 - i});
    }
    for (int i = 0; i < n; i++) {  // p =2 右
      Add({2, i, n - 1}, {5, n - 1, i});
    }

    for (int i = 0; i < n; i++) {  // p =3 上
      Add({3, 0, i}, {2, n - 1, i});
    }
    for (int i = 0; i < n; i++) {  // p =3 下
      Add({3, n - 1, i}, {0, 0, i});
    }
    for (int i = 0; i < n; i++) {  // p =3 左
      Add({3, i, 0}, {4, n - 1 - i, 0});
    }
    for (int i = 0; i < n; i++) {  // p =3 右
      Add({3, i, n - 1}, {5, n - 1 - i, n - 1});
    }

    // p = 4
    for (int i = 0; i < n; i++) {  // 上
      Add({4, 0, i}, {0, i, 0});
    }
    for (int i = 0; i < n; i++) {  //下
      Add({4, n - 1, i}, {2, n - 1 - i, 0});
    }
    for (int i = 0; i < n; i++) {  // 左
      Add({4, i, 0}, {3, n - 1 - i, 0});
    }
    for (int i = 0; i < n; i++) {  // 右
      Add({4, i, n - 1}, {1, i, 0});
    }

    // p = 5
    for (int i = 0; i < n; i++) {  // 上
      Add({5, 0, i}, {0, n - 1 - i, n - 1});
    }
    for (int i = 0; i < n; i++) {  //下
      Add({5, n - 1, i}, {2, i, n - 1});
    }
    for (int i = 0; i < n; i++) {  // 左
      Add({5, i, 0}, {1, i, n - 1});
    }
    for (int i = 0; i < n; i++) {  // 右
      Add({5, i, n - 1}, {3, n - 1 - i, n - 1});
    }

    // for (auto& [a, s] : h) {
    //   auto [p1, x1, y1] = a;
    //   for (auto b : s) {
    //     auto [p2, x2, y2] = b;
    //     if (h.count(b) == 0 || h[b].count(a) == 0) {
    //       printf("init error: \n");
    //       printf("p1=%d (%d,%d) => p2=%d (%d, %d)\n", p1, x1, y1, p2, x2,
    //       y2); if (h.count(b) == 0) {
    //         printf("h.count(b) no find");
    //       }
    //       if (h[b].count(a) == 0) {
    //         printf("h[b].count(a) == 0  no find");
    //       }
    //       return;
    //     }
    //   }
    // }
  }

  //
  bool Check(vector<int>& str, int p) {
    // 当前面是否可以覆盖
    for (int i = 0; i < n; i++) {
      if (str[i] & g[p][i]) return false;
    }

    for (int i = 0; i < n; i++) {  // 上
      int X = 0, Y = i;
      tuple<int, int, int> a = {p, X, Y};
      for (auto [b, x, y] : h[a]) {
        if (1 & (str[X] >> Y) & (g[b][x] >> y)) return false;
      }
    }
    for (int i = 0; i < n; i++) {  // 下
      int X = n - 1, Y = i;
      tuple<int, int, int> a = {p, X, Y};
      for (auto [b, x, y] : h[a]) {
        if (1 & (str[X] >> Y) & (g[b][x] >> y)) return false;
      }
    }
    for (int i = 0; i < n; i++) {  // 左
      int X = i, Y = 0;
      tuple<int, int, int> a = {p, X, Y};
      for (auto [b, x, y] : h[a]) {
        if (1 & (str[X] >> Y) & (g[b][x] >> y)) return false;
      }
    }
    for (int i = 0; i < n; i++) {  // 右
      int X = i, Y = n - 1;
      tuple<int, int, int> a = {p, X, Y};
      for (auto [b, x, y] : h[a]) {
        if (1 & (str[X] >> Y) & (g[b][x] >> y)) return false;
      }
    }
    return true;
  }

  void Cover(vector<int>& str, int p) {
    for (int i = 0; i < n; i++) {
      g[p][i] ^= str[i];
    }

    for (int i = 0; i < n; i++) {  // 上
      int X = 0, Y = i;
      if (!(str[X] & (1 << Y))) continue;
      tuple<int, int, int> a = {p, X, Y};
      for (auto [b, x, y] : h[a]) {
        g[b][x] ^= 1 << y;
      }
    }
    for (int i = 0; i < n; i++) {  // 下
      int X = n - 1, Y = i;
      if (!(str[X] & (1 << Y))) continue;
      tuple<int, int, int> a = {p, X, Y};
      for (auto [b, x, y] : h[a]) {
        g[b][x] ^= 1 << y;
      }
    }
    for (int i = 0; i < n; i++) {  // 左
      int X = i, Y = 0;
      if (!(str[X] & (1 << Y))) continue;
      tuple<int, int, int> a = {p, X, Y};
      for (auto [b, x, y] : h[a]) {
        g[b][x] ^= 1 << y;
      }
    }
    for (int i = 0; i < n; i++) {  // 右
      int X = i, Y = n - 1;
      if (!(str[X] & (1 << Y))) continue;
      tuple<int, int, int> a = {p, X, Y};
      for (auto [b, x, y] : h[a]) {
        g[b][x] ^= 1 << y;
      }
    }
  }

  bool Dfs(int p) {
    if (p == 6) return true;

    for (int i = 0; i < 6; i++) {
      if (use[i]) continue;
      vector<int>& str = shapes[i];
      use[i] = 1;

      for (int j = 0; j < 4; j++) {
        if (Check(str, p)) {
          Cover(str, p);
          if (Dfs(p + 1)) return true;
          Cover(str, p);
        }
        Rotate(str);
      }

      Reverse(str);
      for (int j = 0; j < 4; j++) {
        if (Check(str, p)) {
          Cover(str, p);
          if (Dfs(p + 1)) return true;
          Cover(str, p);
        }
        Rotate(str);
      }
      Reverse(str);

      use[i] = 0;
    }
    return false;
  }

  bool Dfs0(int p) {  // 第一个面随便摆放
    int i = 0;
    vector<int>& str = shapes[0];
    use[i] = 1;
    Cover(str, p);
    return Dfs(p + 1);
  }

 public:
  bool composeCube(vector<vector<string>>& shapes_) {
    n = shapes_.front().size();

    for (auto& shape : shapes_) {
      vector<int> vec;
      for (auto& str : shape) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
          if (str[i] == '1') {
            sum |= 1 << i;
          }
        }
        vec.push_back(sum);
      }
      shapes.push_back(vec);
    }

    Init();
    use.resize(6);
    g.resize(6, vector<int>(n, 0));
    return Dfs0(0);
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  // Solution s;
  // s.n = 9;
  // s.Init();

  return 0;
}
