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
  vll nums;
  vll preSum;
  ll target;

  ll Search(ll add) {
    ll n = nums.size();
    if (n == 0) return 0;
    if (add == 0) return nums.front();

    if (preSum[n - 1] + add >= n * (target - 1)) {
      return target - 1;
    }

    ll l = 0, r = n;  //[l, r)
    while (l < r) {
      ll mid = (l + r) / 2;
      if ((mid + 1) * nums[mid] <= preSum[mid] + add) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }

    return min((preSum[r - 1] + add) / r, target - 1);
  }

 public:
  ll maximumBeauty(vector<int>& flowers, long long newFlowers, int target_,
                   int full, int partial) {
    target = target_;

    ll fullNum = 0;
    for (auto v : flowers) {
      if (v >= target) {
        fullNum++;
      } else {
        nums.push_back(v);
      }
    }
    sort(all(nums));

    int n = nums.size();
    preSum.resize(n, 0);
    rep(i, n) {  //
      // printf("i=%lld v=%lld\n", i, nums[i]);
      if (i == 0) {
        preSum[i] = nums[i];
      } else {
        preSum[i] = preSum[i - 1] + nums[i];
      }
    }

    ll ans = 0;
    ll minVal = Search(newFlowers);
    ans = max(ans, fullNum * full + partial * minVal);

    // printf("ans=%lld fullNum=%lld minVal=%lld\n", ans, fullNum, minVal);
    while (newFlowers && !nums.empty()) {
      // printf("newFlowers=%d num=%d\n", newFlowers, nums.size());
      nums.back() += newFlowers;
      newFlowers = 0;
      if (nums.back() >= target) {
        fullNum++;
        newFlowers = nums.back() - target;
        nums.pop_back();
      }
      // printf("pro: newFlowers=%d num=%d\n", newFlowers, nums.size());

      ll minVal = Search(newFlowers);
      ans = max(ans, fullNum * full + partial * minVal);
      // printf("ans=%lld fullNum=%lld minVal=%lld\n", ans, fullNum, minVal);
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
