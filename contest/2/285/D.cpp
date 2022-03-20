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

struct Node {
  ll l = 0, r = 0;
  bool flag = false;
};

class Solution {
  max_queue<pll> heap;
  vector<Node> buf;
  map<ll, ll> m;

  void Add(ll l, ll r) {
    buf.push_back(Node{l, r, true});
    heap.push({r - l + 1, buf.size() - 1});
    m[l] = buf.size() - 1;
  }
  void Del(ll x) {
    buf[x].flag = false;
    m.erase(buf[x].l);
  }
  ll Search(ll x) {
    auto it = m.upper_bound(x);
    it--;
    return it->second;
  }

 public:
  vector<int> longestRepeating(string& s, string& ss, vector<int>& nums) {
    // 线段树做更简单些
    s.push_back('-');
    ll n = s.size();

    ll pre = 0;
    rep(i, n) {
      if (s[i] == s[pre]) {
        continue;
      } else {
        Add(pre, i - 1);
        pre = i;
      }
    }
    Add(pre, pre);

    vi ans(nums.size(), 1);

    rep(i, nums.size()) {
      char c = ss[i];
      int j = nums[i];
      printf("s=%s j=%d c=%c\n", s.c_str(), j, c);

      if (s[j] == c) {  // 不变
        ans[i] = heap.top().first;
        printf("nochange, ans=%d\n", ans[i]);
        continue;
      }
      s[j] = c;
      printf("after=%s\n", s.c_str());

      // 分几种情况：拆分出新的线段，合并新的线段
      ll l, r;
      if (1) {
        ll p = Search(j);
        Del(p);

        l = buf[p].l, r = buf[p].r;
      }
      printf("base l=%lld r=%lld\n", l, r);

      // 在线段中间，被拆分，旧的线段废弃
      if (l < j && j < r) {
        printf("mid\n");
        // [l, j-1] [j, j] [j+1, r]
        Add(l, j - 1);
        Add(j, j);
        Add(j + 1, r);
      } else {  // 在边界
        if (l == j && j < r) {
          printf("left\n");
          // [l+1, r]
          Add(l + 1, r);
          r = l;
        } else if (r == j && r > j) {
          printf("right\n");
          // [l, r-1]
          Add(l, r - 1);
          l = r;
        } else {  // l == r
          printf("one\n");
        }

        for (auto& pp : m) {
          ll p = pp.second;
          printf("index=%lld, l=%lld r=%lld flag=%d\n", p, buf[p].l, buf[p].r,
                 buf[p].flag);
        }

        if (l > 0 && s[l - 1] == s[l]) {  // 左合并
          printf("l-1=%lld\n", l - 1);
          ll p = Search(l - 1);
          Del(p);
          l = buf[p].l;
          printf("merge left,  del l=%lld r=%lld\n", buf[p].l, buf[p].r);
        }

        if (s[r] == s[r + 1]) {  // 右合并
          printf("merge right\n");
          ll p = Search(r + 1);
          Del(p);
          r = buf[p].r;
        }

        Add(l, r);
      }

      while (buf[heap.top().second].flag == false) {
        heap.pop();
      }

      ans[i] = heap.top().first;
      ll p = heap.top().second;

      printf("ans=%d l=%lld r=%lld\n", ans[i], buf[p].l, buf[p].r);
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
