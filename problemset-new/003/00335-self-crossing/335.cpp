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

typedef long long ll;
enum { TOP = 0, LEFT = 1, BOTTOM = 2, RIGHT = 3 };
ll sign[4] = {1, -1, -1, 1};
class Solution {
  ll closeRec[4];
  ll openRec[4];
  vector<int> distance;
  int n;

  bool ChekcIn(int p, int dir) {  // 判断内卷是否成立
    while (p < n) {
      ll s = sign[dir];
      ll tmp = closeRec[R(dir)] + s * distance[p];
      if (s * tmp >= s * closeRec[dir]) {
        return true;
      }
      closeRec[dir] = tmp;
      dir = N(dir);
      p++;
    }

    return false;
  }

  int R(int d) { return (d + 2) % 4; }
  int N(int d) { return (d + 1) % 4; }

 public:
  bool isSelfCrossing(vector<int>& distance_) {
    distance.swap(distance_);
    n = distance.size();
    if (n < 4) return false;

    memset(closeRec, 0, sizeof(closeRec));
    memset(openRec, 0, sizeof(openRec));

    closeRec[TOP] = distance[0];
    closeRec[LEFT] = 0 - distance[1];

    openRec[LEFT] = closeRec[LEFT];
    openRec[BOTTOM] = closeRec[TOP] - distance[2];
    openRec[RIGHT] = closeRec[LEFT] + distance[3];

    if (openRec[BOTTOM] >= closeRec[BOTTOM] &&
        openRec[RIGHT] >= closeRec[RIGHT]) {
      return true;  // 前四步形成闭环
    }

    if (openRec[RIGHT] <= closeRec[RIGHT]) {  // 前四步开始内卷
      if (openRec[RIGHT] == closeRec[RIGHT]) {
        closeRec[TOP] = closeRec[BOTTOM];  // 特殊边界，与起点一条直线
      }
      closeRec[BOTTOM] = openRec[BOTTOM];
      closeRec[RIGHT] = openRec[RIGHT];
      return ChekcIn(4, TOP);
    }

    int p = 4;
    int dir = TOP;
    while (p < n) {
      ll s = sign[dir];

    //   printf("closeRec: ");
    //   for (int i = 0; i < 4; i++) {
    //     printf("%lld ", closeRec[i]);
    //   }
    //   printf("\n");

    //   printf("openRec: ");
    //   for (int i = 0; i < 4; i++) {
    //     printf("%lld ", openRec[i]);
    //   }
    //   printf("\n");

    //   printf("dir=%d d=%d\n", dir, distance[p]);

      openRec[dir] = openRec[R(dir)] + s * distance[p];
    //   printf("new pos=%lld\n", openRec[dir]);
      if (s * openRec[dir] < s * closeRec[R(dir)]) {  // 第一部分内卷
        for (int i = 0; i < 4; i++) {
          closeRec[i] = openRec[i];
        }
        // printf("p=%d dir=%d checkin 1\n", p, dir);
        return ChekcIn(p + 1, N(dir));
      } else if (s * openRec[dir] <= s * closeRec[dir]) {  // 第二部分内卷
        openRec[N(dir)] = closeRec[R(N(dir))];
        for (int i = 0; i < 4; i++) {
          closeRec[i] = openRec[i];
        }
        // printf("p=%d dir=%d checkin 2\n", p, dir);
        return ChekcIn(p + 1, N(dir));
      } else {
        closeRec[R(dir)] = openRec[R(dir)];  // 外卷，下侧扩张
      }
    //   printf("p=%d checkout\n", p);
      dir = N(dir);
      p++;
    }

    return false;
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
