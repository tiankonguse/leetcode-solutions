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

const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
  int h, w;
  int n;
  int edgeNum;
  vector<vector<pair<int, int>>> g;
  int index = 0;
  void add(int u, int v) {
    g[u].push_back({v, index});
    g[v].push_back({u, index});
    index++;
  }
  unordered_set<int> s;
  vector<int> flag;
  int t = 0;
  int Check(int x) {  //
    flag.clear();
    flag.resize(n, 0);

    int delNum = 0;
    queue<pair<int, int>> que;  // {x, t}
    que.push({x, 0});
    flag[x] = 1;
    int ans = 0;

    while (!que.empty()) {
      auto [u, t] = que.front();
      que.pop();

      for (auto [v, I] : g[u]) {
        if (s.count(I)) continue;
        ans = max(ans, t + 1);
        delNum++;
        if (flag[v] == 1) continue;

        que.push({v, t + 1});
        flag[v] = 1;
      }
    }

    if (delNum != edgeNum) {
      return inf;
    }
    return ans;
  }

 public:
  vector<int> lightSticks(int height, int width, vector<int>& indices) {
    s.insert(indices.begin(), indices.end());

    h = height + 1;
    w = width + 1;
    n = h * w;
    g.resize(n);

    for (int j = 1; j < w; j++) {
      int u = j - 1, v = j;
      add(u, v);
    }
    for (int i = 1; i < h; i++) {
      for (int j = 0; j < w; j++) {  // 竖线
        int u = i * w + j;
        int v = u - w;
        add(u, v);
      }

      for (int j = 1; j < w; j++) {  // 横线
        int u = i * w + j;
        int v = u + 1;
        add(u, v);
      }
    }

    edgeNum = index - indices.size();

    vector<int> ans;
    ans.reserve(n);
    int minT = inf;
    for (int i = 0; i < n; i++) {
      int t = Check(i);
      if (t == minT) {
        ans.push_back(i);
      } else if (t < minT) {
        ans.clear();
        ans.push_back(i);
        minT = t;
      }
    }
    if (minT == inf) {
      ans.clear();
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
