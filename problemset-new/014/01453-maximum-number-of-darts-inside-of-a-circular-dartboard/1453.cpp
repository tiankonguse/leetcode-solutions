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
#define ALL(A) A.begin(), A.end()
#define LLA(A) A.rbegin(), A.rend()
#define sz(x) (int)(x).size()
#define SZ(A) int((A).size())
#define CPY(A, B) memcpy(A, B, sizeof(A))
#define CTN(T, x) (T.find(x) != T.end())
#define PB push_back
#define MP(A, B) make_pair(A, B)
#define fi first
#define se second

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

template <class T>
inline void RST(T& A) {
  memset(A, 0, sizeof(A));
}
template <class T>
inline void FLC(T& A, int x) {
  memset(A, x, sizeof(A));
}
template <class T>
inline void CLR(T& A) {
  A.clear();
}
template <class T>
T& chmin(T& a, T b) {
  if (a == -1) {
    a = b;
  } else {
    a = min(a, b);
  }
  return a;
}
template <class T>
T& chmax(T& a, T b) {
  if (a == -1) {
    a = b;
  } else {
    a = max(a, b);
  }
  return a;
}

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;
constexpr ld EPS = 1e-12;
ld PI = acos(-1.0);

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
// LONG_MIN(10进制 10位), LONG_MAX(10进制 19位)

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

vector 去重
sort(nums.begin(), nums.end());
nums.erase(unique(nums.begin(), nums.end()), nums.end());

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

srand((unsigned)time(NULL));
rand();

mt19937 gen{random_device{}()};
uniform_real_distribution<double> dis(min, max);
function<double(void)> Rand = [that = this]() { return that->dis(that->gen); };

*/

class Solution {
  vector<vector<int>> points_;
  int r_;
  int ans_;
  const double kEps = 1e-5;  // double类型等于0统一用是否<0来判断

  void testCenter(double x0, double y0) {
    int ans = 0;
    long long r2 = r_ * r_;
    for (auto& v : points_) {
      double x = v[0] - x0, y = v[1] - y0;
      if (x * x + y * y <= r2 + kEps) {
        ans++;
      }
    }
    ans_ = max(ans_, ans);
  }

  void testTwoPoint() {
    for (int i = 0; i < points_.size(); i++) {
      auto& p1 = points_[i];
      for (int j = i + 1; j < points_.size(); j++) {
        auto& p2 = points_[j];
        testCenter((p1[0] + p2[0] * 1.0) / 2, (p1[1] + p2[1] * 1.0) / 2);
      }
    }
  }

  bool isLine(vector<int>& p1, vector<int>& p2, vector<int>& p3) {
    int x1 = p1[0], y1 = p1[1];
    int x2 = p2[0], y2 = p2[1];
    int x3 = p3[0], y3 = p3[1];
    return (y3 - y1) * (x2 - x1) - (y2 - y1) * (x3 - x1) == 0;
  }
  void getCenter(vector<int>& p1, vector<int>& p2, vector<int>& p3, double& x,
                 double& y, double& r) {
    double x1 = p1[0], y1 = p1[1];
    double x2 = p2[0], y2 = p2[1];
    double x3 = p3[0], y3 = p3[1];
    x = ((y2 - y1) * (y3 * y3 - y1 * y1 + x3 * x3 - x1 * x1) -
         (y3 - y1) * (y2 * y2 - y1 * y1 + x2 * x2 - x1 * x1)) /
        (2.0 * ((x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1)));
    y = ((x2 - x1) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1) -
         (x3 - x1) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)) /
        (2.0 * ((y3 - y1) * (x2 - x1) - (y2 - y1) * (x3 - x1)));
    r = (x1 - x) * (x1 - x + (y1 - y) * (y1 - y));
  }
  void testThreePoint() {
    auto& points = points_;
    for (int i = 0; i < points.size(); i++) {
      auto& p1 = points[i];
      for (int j = i + 1; j < points.size(); j++) {
        auto& p2 = points[j];
        for (int k = j + 1; k < points.size(); k++) {
          auto& p3 = points[k];
          if (isLine(p1, p2, p3)) {
            continue;
          }
          double x = 0, y = 0, r = 0;
          getCenter(p1, p2, p3, x, y, r);
          if (r + kEps > r_) {
            // continue;
          }
          testCenter(x, y);
        }
      }
    }
  }

 public:
  int numPoints(vector<vector<int>>& points, int r) {
    points_.swap(points);
    r_ = r;

    ans_ = 1;
    testTwoPoint();
    testThreePoint();
    return ans_;
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
