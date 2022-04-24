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

typedef long long ll;
class TreeArray {
 public:
  void Init(int n_) {
    n = n_;
    c.resize(n + 100, 0);
  }

  ll Query(int x) {
    ll s = 0;
    while (x > 0) {
      s += c[x];
      x -= Lowbit(x);
    }
    return s;
  }

  ll Query(int l, int r) { return Query(r) - Query(l - 1); }

  void Add(int x, ll v) {
    while (x <= n) {
      c[x] += v;
      x += Lowbit(x);
    }
  }

 private:
  int Lowbit(int x) { return x & -x; }
  vector<ll> c;
  int n;
};
class Solution {
  unordered_map<int, int> h;
  vector<int> ys;
  int n;
  void Add(int y) {
    if (h.count(y) == 0) {
      h[y] = 0;
      ys.push_back(y);
    }
  }
  void Init() {
    sort(ys.begin(), ys.end());
    n = ys.size();
    for (int i = 0; i < n; i++) {
      int v = ys[i];
      h[v] = i + 1;
    }
  }

 public:
  vector<int> countRectangles(vector<vector<int>>& rectangles,
                              vector<vector<int>>& points) {
    for (auto& vs : rectangles) {
      int x = vs[0], y = vs[1];
      Add(y);
    }
    for (auto& vs : points) {
      int x = vs[0], y = vs[1];
      Add(y);
    }
    Init();

    TreeArray treeArray;
    treeArray.Init(n);
    for (auto& vs : rectangles) {
      int x = vs[0], y = vs[1];
      treeArray.Add(h[y], 1);
    }

    sort(rectangles.begin(), rectangles.end());
    vector<tuple<int, int, int>> nums;
    for (int i = 0; i < points.size(); i++) {
      auto& vs = points[i];
      int x = vs[0], y = vs[1];
      nums.push_back({x, y, i});
    }
    sort(nums.begin(), nums.end());

    vector<int> ans(nums.size(), 0);
    int l = 0, r = rectangles.size();
    for (auto& [x, y, i] : nums) {
      while (l < r && rectangles[l][0] < x) {
        treeArray.Add(h[rectangles[l][1]], -1);
        l++;
      }
    //   printf("query(%d, %d) = %d\n", x, y, treeArray.Query(y, n));
      ans[i] = treeArray.Query(h[y], n);
    }
    return ans;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
