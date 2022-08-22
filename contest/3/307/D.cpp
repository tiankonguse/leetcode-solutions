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

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
  ll K;

  // 正数，选择的越小，剩余的就越大
  ll Solver(vector<ll>& nums, vector<ll>& ans) {
    if (nums.size() == 0) return 0;
    sort(nums.begin(), nums.end());

    ll n = nums.size();

    max_queue<ll> heap;  // 保存最小的 K 个数字

    ll SUM = 0;
    for (auto v : nums) {
      SUM += v;
    }

    min_queue<pair<ll, ll>> que;  // <sum, offset>
    que.push({0, 0});

    while (!que.empty()) {
      auto [sum, offset] = que.top();
      que.pop();
      if (heap.size() >= K && sum > heap.top()) continue;

      ll maxOffset = min(n, offset + K + 1);
      for (int i = offset; i < maxOffset; i++) {
        ll tmpSum = sum + nums[i];

        if (heap.size() < K) {
          heap.push(tmpSum);
          que.push({tmpSum, i + 1});
        } else if (heap.size() >= K && tmpSum < heap.top()) {
          heap.push(tmpSum);
          que.push({tmpSum, i + 1});
          while (heap.size() > K) heap.pop();
        } else {
          break;
        }
      }
    }

    while (heap.size() > K) heap.pop();

    ans.reserve(heap.size());
    while (!heap.empty()) {
      ll v = heap.top();
      heap.pop();
      ans.push_back(v);
    }

    sort(ans.begin(), ans.end());
    return SUM;
  }

  bool ShouldFix(vector<ll>& nums, int k) {
    int n = nums.size();
    if (n > 11) return false;
    int maxNum = 1 << n;
    return maxNum <= k;
  }

 public:
  long long kSum(vector<int>& nums, int k) {
    K = k;
    vector<ll> nums1, nums2;
    vector<ll> ans1, ans2;

    nums1.reserve(nums.size());
    nums1.reserve(nums.size());
    for (auto v : nums) {
      if (v >= 0) {
        nums1.push_back(v);
      } else {
        nums2.push_back(-v);
      }
    }
    ll sum1 = Solver(nums1, ans1);
    ll sum2 = Solver(nums2, ans2);
    ans1.push_back(0);


    min_queue<ll> heap;

    for (auto& v : ans1) {
      v = sum1 - v;
      heap.push(v);
      // printf("v1=%lld\n", v);
    }
    // printf("n1=%lld ans1=%lld n2=%lld ans2=%lld\n", nums1.size(), ans1.size(), nums2.size(), ans2.size());
    // if (ShouldFix(nums1, k)) {
    //   ans1.pop_back();
    // }
    printf("n1=%lld ans1=%lld n2=%lld ans2=%lld\n", nums1.size(), ans1.size(), nums2.size(), ans2.size());

    // for (auto& v : ans2) {
    //     v = -v;
    //   heap.push(v);
    //   // printf("v2=%lld\n", v);
    // }
    while(heap.size() > k)heap.pop();

    for (int i = 0; i < ans1.size(); i++) {
      for (int j = 0; j < ans2.size(); j++) {
        // printf("v1+v2=%lld\n", ans1[i] + ans2[j]);
        if (heap.size() == k && ans1[i] - ans2[j] <= heap.top()) {
          break;
        }
        heap.push(ans1[i] - ans2[j]);
        while(heap.size() > k)heap.pop();
      }
    }

    // int index = 1;
    // while (!heap.empty()) {
    //   printf("index=%d v=%lld\n", index++, heap.top());
    //   heap.pop();
    // }

    return heap.top();
  }
};

/*
[362742000,633839330,573455625,-497207607,-947134176]
28
-810502453
*/

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
