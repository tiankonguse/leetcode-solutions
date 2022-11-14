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

/*
  sum(k) / k    = S - sum(k)) / (n - k)
 sum(k) * (n-k) = (S - sum(k)) * k
 sum(k) * n - sum(k) * k = S * k - sum(k) * k
 sum(k) * n = S * k
 sum(k)/k = S/n
*/

typedef long long ll;
class Solution {
  vector<int> nums;
  unordered_set<ll> h;

  bool Dfs(int l, int r, ll sum, int num) {
    if (num) {
      h.insert(sum);
      if (sum == 0) {
        //   printf("check half zero\n");
        return true;
      }
    }
    if (l == r) return false;
    if (Dfs(l + 1, r, sum + nums[l], num + 1)) {
      // printf("select %d\n", nums[l]);
      return true;
    }
    return Dfs(l + 1, r, sum, num);
  }

  int mid;
  bool Check(int l, int r, ll sum, int num) {
    if (num) {
      if (sum == 0) {
        //   printf("check half zero\n");
        return true;
      }
      if (num != r - mid && h.count(-sum)) {
        //   printf("check eq, l=%d r=%d num=%d\n", mid, r, num);
        return true;
      }
    }
    if (l == r) return false;
    if (Check(l + 1, r, sum + nums[l], num + 1)) {
      // printf("select %d\n", nums[l]);
      return true;
    }
    return Check(l + 1, r, sum, num);
  }

 public:
  bool splitArraySameAverage(vector<int>& nums_) {
    nums.swap(nums_);
    int n = nums.size();
    if (n == 1) return false;
    ll sum = 0;
    for (int v : nums) {
      sum += v;
    }
    for (auto& v : nums) {
      v = v * n - sum;
      //   printf("%d ", v);
    }
    // printf("\n");
    mid = n / 2;  //[0, mid) [mid, n)
    if (Dfs(0, mid, 0, 0)) {
      return true;
    }
    return Check(mid, n, 0, 0);
  }
};

// [73,37,34,95,4,97,22,53,55,52,46,44,71,24,26,35,96,3]
// [3863,703,1799,327,3682,4330,3388,6187,5330,6572,938,6842,678,9837,8256,6886,2204,5262,6643,829,745,8755,3549,6627,1633,4290,7]
// [0,13,13,7,5,0,10,19,5]
// [1,2,3,4,5,6,7,8]
// [3,1]
// [6,8,18,3,1]
// [5000,5001,5002,5003,5004,5005,5006,5007,5008,5009,5010,5011,5012,5013,5114,5115,5116,5117,5118,5119,5120,5121,5122,5123,5124,5125,5126,5127,6128,7724]
// [60,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30]

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
