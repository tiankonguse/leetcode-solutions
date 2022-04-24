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
int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
  vector<vector<ll>> preAns;
  vector<vector<ll>> tmpAns;
  ll preT;
  void Move(const ll t) {
    if (preT + 4 <= t) {  // 可以到达所有位置
      ll maxVal = preAns[0][0];
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          maxVal = max(maxVal, preAns[i][j]);
        }
      }
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          preAns[i][j] = maxVal;
        }
      }
      preT = t;
      return;
    }

    // printf("preT=%d\n", preT);
    // for (int i = 0; i < 3; i++) {
    //   for (int j = 0; j < 3; j++) {
    //     printf("%d ", preAns[i][j]);
    //   }
    //   printf("\n");
    // }

    ll maxStep = 3;
    tmpAns = preAns;
    while (preT < t && maxStep > 0) {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          for (int k = 0; k < 4; k++) {
            int X = i + dir4[k][0];
            int Y = j + dir4[k][1];
            if (X < 0 || X >= 3 || Y < 0 || Y >= 3) continue;
            tmpAns[X][Y] = max(tmpAns[X][Y], preAns[i][j]);
          }
        }
      }
      preAns = tmpAns;
      maxStep--;
      preT++;
    }
    preT = t;

    // printf("t=%d\n", t);
    // for (int i = 0; i < 3; i++) {
    //   for (int j = 0; j < 3; j++) {
    //     printf("%d ", preAns[i][j]);
    //   }
    //   printf("\n");
    // }
  }

 public:
  int getMaximumNumber(vector<vector<int>>& moles) {
    sort(moles.begin(), moles.end());
    preAns.resize(3, vector<ll>(3, -1));
    tmpAns.resize(3, vector<ll>(3, -1));
    preAns[1][1] = 0;
    preT = 0;

    ll ans = 0;
    for (auto& v : moles) {
      ll t = v[0], x = v[1], y = v[2];
      Move(t);
      if (preAns[x][y] >= 0) {
        preAns[x][y]++;
      }
      ans = max(ans, preAns[x][y]);
    }
    return ans;
  }
};

int main() {
  vector<vector<int>> tmpAns;
  tmpAns.resize(3, vector<int>(3, -1));
  tmpAns[1][1] = 1;
  tmpAns.clear();
  tmpAns.resize(3, vector<int>(3, -1));
  printf("%d\n", tmpAns[1][1]);

  // int ans = 2;
  // vvi nums = {{1, 1, 0}};
  // TEST_SMP1(Solution, getMaximumNumber, ans, nums);

  return 0;
}
