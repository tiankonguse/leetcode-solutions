#include <bits/stdc++.h>

using namespace std;

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
// const int mod = 1e9 + 7;

#define FOR(i, a, b) for (auto i = a; i < b; ++i)
#define FOR1(i, a, b) for (auto i = a; i <= b; ++i)
#define DWN(i, b, a) for (auto i = b - 1; i >= a; --i)
#define DWN1(i, b, a) for (auto i = b; i >= a; --i)

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

lower_bound 大于等于
upper_bound 大于

vector / array : upper_bound(vec.begin(), vec.end(), v)
map: m.upper_bound(v)

区间 [l,r]内满足的个数：
upper_bound(vec.begin(), vec.end(), r) - lower_bound(vec.begin(), vec.end(), l);
std::distance(v.begin(), it)
map/set distance 复杂度 O(N)
vector/数组 distance 复杂度 O(1)

vector预先分配内存 reserve
反转 reverse(v.begin(), v.end())


sum = accumulate(a.begin(), a.end(), 0ll);
unordered_map / unordered_set

__builtin_popcount 一的个数

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

ll n, L, R;
vector<ll> nums;

ll Solver(ll x, ll y) {
  int NUM = 2;
  if (L == R) {
    NUM = 1;
  }

  ll l = x, r = x;
  ll ans = 0;
  map<ll, ll> m;
  while (r <= y) {
    while (m.size() != NUM && r <= y) {
      if (nums[r] == L) {
        m[L] = r;
      } else if (nums[r] == R) {
        m[R] = r;
      } else {
      }
      r++;
    }
    if (m.size() != NUM) break;
    ll minPos = min(m[L], m[R]);
    ll maxPos = max(m[L], m[R]);
    ll tmp = (minPos - l + 1) * (y - maxPos + 1);
    // printf("min=%lld max=%lld [%lld,%lld) ans=%lld\n", minPos, maxPos, l, r,
    //        tmp);
    ans += tmp;

    while (m.size() == NUM) {
      if (nums[l] == L && m[L] == l) {
        m.erase(L);
      } else if (nums[l] == R && m[R] == l) {
        m.erase(R);
      } else {
      }
      l++;
    }
  }

  return ans;
}

int main() {
  scanf("%lld", &n);
  scanf("%lld%lld", &R, &L);
  nums.resize(n);

  rep(i, n) {  //
    scanf("%lld", &nums[i]);
  }
  nums.push_back(R + 1);
  n = nums.size();

  ll sum = 0;

  ll l = 0, r = 0;
  bool flag = false;
  rep(i, n) {
    ll v = nums[i];
    if (v >= L && v <= R) {
      if (flag == false) {  // 首部
        flag = true;
        l = r = i;
      } else {
        r = i;
      }
    } else {  // 找到一个区间
      if (flag) {
        // printf("l=%lld r=%lld\n", l, r);
        sum += Solver(l, r);
      }
      flag = false;
    }
  }

  printf("%lld\n", sum);
  return 0;
}
