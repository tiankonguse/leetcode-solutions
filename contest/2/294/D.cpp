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
// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
struct SegTree {
  vector<ll> minVal;
  vector<ll> str;

  void Init(int n) {
    maxNM = n;
    minVal.resize(maxNM << 2, 0);
    str.resize(maxNM + 2);
  }

  void PushUp(int rt) {
    minVal[rt] = min(minVal[rt << 1], minVal[rt << 1 | 1]);
  }

  void Build(int l = 1, int r = maxNM, int rt = 1) {
    if (l == r) {
      minVal[rt] = str[l];
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt);
  }
  ll QueryMin(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return minVal[rt];
    }
    int m = (l + r) >> 1;
    ll ret = __LONG_LONG_MAX__;
    if (L <= m) {
      ret = min(ret, QueryMin(L, R, lson));
    }
    if (m < R) {
      ret = min(ret, QueryMin(L, R, rson));
    }
    return ret;
  }
};

SegTree segTree;

const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  int totalStrength(vector<int>& nums) {
    if (nums.size() == 1) return (ll(nums[0]) * nums[0]) % mod;

    ll n = nums.size();
    segTree.Init(n + 1);
    for (int i = 1; i <= n; i++) {
      segTree.str[i] = nums[i - 1];
    }
    segTree.Build();

    vector<ll> preSum(n + 2, 0), afterSum(n + 2, 0);
    vector<ll> preSum2(n + 2, 0), afterSum2(n + 2, 0);

    for (int i = 1; i <= n; i++) {
      preSum[i] = (preSum[i - 1] + nums[i - 1]) % mod;
      preSum2[i] = (preSum2[i - 1] + preSum[i]) % mod;
      // printf("pre i=%d sum=%lld sumsum=%lld\n", i, preSum[i], preSum2[i]);
    }

    for (int i = n; i >= 1; i--) {
      afterSum[i] = (afterSum[i + 1] + nums[i - 1]) % mod;
      afterSum2[i] = (afterSum2[i + 1] + afterSum[i]) % mod;
      // printf("after i=%d sum=%lld sumsum=%lld\n", i, afterSum[i],
      // afterSum2[i]);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {  // 以 i 为最小值
      ll l = i, r = i;
      ll v = nums[i - 1];

      if (1 < l && nums[i - 2] > v) {
        int L = 1, R = i;  // [L, R)

        while (L < R) {
          int mid = (L + R) / 2;
          ll minVal = segTree.QueryMin(mid, R - 1);
          if (minVal <= v) {
            L = mid + 1;
          } else {
            R = mid;
          }
        }

        l = L;
      }

      if (i < n && nums[i] >= v) {
        ll L = i + 1, R = n + 1;  // [L, R)
        while (L < R) {
          ll mid = (L + R) / 2;
          ll minVal = segTree.QueryMin(L, mid);
          if (minVal < v) {
            R = mid;
          } else {
            L = mid + 1;
          }
        }

        r = min(R, n);
        if (nums[r - 1] < v) {
          r--;
        }
      }

      // printf("i=%d v=%lld l=%lld r=%lld\n", i, v, l, r);

      ll sumr = (preSum2[r] - preSum2[i] - preSum[i] * (r - i)) % mod;
      sumr = (sumr + mod) % mod;
      ll suml = (afterSum2[l] - afterSum2[i] - afterSum[i] * (i - l)) % mod;
      suml = (suml + mod) % mod;

      ll L = i - l + 1;
      ll R = r - i + 1;
      ll tmp = (sumr * L + suml * R + v * L * R) % mod;
      ans = (ans + tmp * v) % mod;
      // printf("L=%lld R=%lld sumR=%lld sumL=%lld, tmp=%lld ans=%lld\n", L, R,
      // sumr, suml, tmp, ans);
    }

    return ans;
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
