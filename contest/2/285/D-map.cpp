#include "base.h"

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
#define rrep1(i, n) for (ll i = (n); i >= 0; i--)
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
  map<ll, ll> m;
  map<ll, set<ll>> heap;

  void Add(ll l, ll r) {
    ll d = r - l + 1;
    m[l] = r;
    heap[d].insert(l);
  }
  void Del(ll l, ll r) {
    ll d = r - l + 1;
    m.erase(l);
    if (heap[d].size() == 1) {
      heap.erase(d);
    } else {
      heap[d].erase(l);
    }
  }
  pll Search(ll x) {
    auto it = m.upper_bound(x);
    it--;
    return {it->first, it->second};
  }
  ll Top() { return heap.rbegin()->first; }

 public:
  vector<int> longestRepeating(string& s, string& ss, vector<int>& nums) {
    s = "-" + s + '-';  // 前后打桩
    ll n = s.size();
    ll k = nums.size();

    ll pre = 0;
    rep(i, n) {
      if (s[i] == s[pre]) {
        continue;
      }
      Add(pre, i - 1);
      pre = i;
    }
    Add(pre, pre);

    vi ans(k, 1);

    rep(i, k) {
      const char c = ss[i];
      const int j = nums[i] + 1;

      if (s[j] == c) {  // 不变
        ans[i] = Top();
        continue;
      }
      s[j] = c;

      auto [l, r] = Search(j);
      Del(l, r);  // 删除当前线段

      if (l < j && j < r) {  // 一分为三
        Add(l, j - 1), Add(j, j), Add(j + 1, r);
      } else {
        if (l < r) {     // 拆分出新线段
          if (l == j) {  //  左边界
            Add(l + 1, r);
          } else {  // 右边界
            Add(l, r - 1);
          }
        }
        l = r = j;               // 不再中间，拆分之后长度肯定是 1
        if (s[l - 1] == s[l]) {  // 左合并
          auto [L, R] = Search(l - 1);
          Del(L, R);
          L = l;
        }
        if (s[r] == s[r + 1]) {  // 右合并
          auto [L, R] = Search(r + 1);
          Del(L, R);
          r = R;
        }
        Add(l, r);
      }

      ans[i] = Top();
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
