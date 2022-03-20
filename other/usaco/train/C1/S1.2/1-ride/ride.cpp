/*
ID: tiankonguse
TASK: ride
PROG: ride
LANG: C++
*/
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

struct mint {
  static const long long mod = 1000000007;
  long long x;
  mint(long long x = 0) : x((x % mod + mod) % mod) {}
  mint operator-() const { return mint(-x); }
  mint& operator+=(const mint& a) {
    if ((x += a.x) >= mod) x -= mod;
    return *this;
  }
  mint& operator-=(const mint& a) {
    if ((x += mod - a.x) >= mod) x -= mod;
    return *this;
  }
  mint& operator*=(const mint& a) {
    (x *= a.x) %= mod;
    return *this;
  }

  friend const mint operator+(const mint& a, const mint& b) {
    mint ret = a;
    return ret += b;
  }
  friend const mint operator-(const mint& a, const mint& b) {
    mint ret = a;
    return ret -= b;
  }
  friend const mint operator*(const mint& a, const mint& b) {
    mint ret = a;
    return ret *= b;
  }
  friend ostream& operator<<(ostream& s, const mint& a) { return s << a.x; }

  mint pow(long long t) const {
    if (!t) return 1;
    mint a = pow(t >> 1);
    a *= a;
    if (t & 1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const { return pow(mod - 2); }
  mint& operator/=(const mint a) { return (*this) *= a.inv(); }
  friend const mint operator/(const mint& a, const mint& b) {
    mint ret = a;
    return ret /= b;
  }
};

struct combi {
  const static long long mod = mint::mod;
  int n;
  vector<mint> fac, finv, inv;

  combi(int _n) : n(_n + 1), fac(n, 1), finv(n, 1), inv(n, 1) {
    for (int i = 2; i < n; ++i) {
      fac[i] = fac[i - 1] * i;
      inv[i] = -inv[mod % i] * (mod / i);
      finv[i] = finv[i - 1] * inv[i];
    }
  };

  mint get(int n, int k) {
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    mint ret = fac[n] * finv[k] * finv[n - k];
    return ret;
  }
};

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

mutex mtx;       // 互斥量，锁，定义一个即可
condition_variable cv; // 条件变量
cv.notify_one(); // 事件通知
unique_lock<mutex> lck(mtx);
cv.wait(lck); //等待事件

atomic_int tick; // 原子计数
this_thread::yield();  // 线程 sleep

#include <semaphore.h> // 需要手动包含信号量头文件
sem_t sem_done;
sem_init(&bar_done, 0 , 1);
sem_wait(&bar_done);
sem_post(&foo_done);

*/

const char* in = "ride.in";
const char* out = "ride.out";

char str[2][10];

ll Solver(char* s) {
  ll ans = 1;
  while (*s) {
    ans = (ans * (*s - 'A' + 1)) % 47;
    s++;
  }
  return ans;
}
int main() {
#ifndef USACO_LOCAL_JUDGE
  freopen(in, "r", stdin);
  freopen(out, "w", stdout);
#endif

  scanf("%s%s", str[0], str[1]);
  printf("%s\n", Solver(str[0]) == Solver(str[1]) ? "GO" : "STAY");

  return 0;
}
