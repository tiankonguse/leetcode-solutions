#include <bits/stdc++.h>

using namespace std;

#define myprintfex(format, args...) printf("line[%d]" format, __LINE__, ##args)
// #define myprintfex(format, args...)

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

#define FOR(i, a, b) for (auto i = a; i < b; ++i)
#define FOR1(i, a, b) for (auto i = a; i <= b; ++i)
#define DWN(i, b, a) for (auto i = b - 1; i >= a; --i)
#define DWN1(i, b, a) for (auto i = b; i >= a; --i)

#define IN_INT(x) scanf("%d", &x)
#define IN_LONG(x) scanf("%lld", &x)
#define IN_NUM(x) scanf("%lf", &x)
#define IN_STR(x) scanf("%s", x)

#define OUT_INT(x) printf("%d", x)
#define OUT_LONG(x) printf("%d", x)
#define OUT_NUM(x) printf("%lf", x)
#define OUT_STR(x) printf("%s", x)
#define OUT_SPACE() putchar(' ')
#define OUT_LINE() putchar('\n')

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

int& myMax(int& a, int b) {
  if (a < 0) {
    a = b;
  } else if (a < b) {
    a = b;
  }
  return a;
}
int& myMin(int& a, int b) {
  if (a < 0) {
    a = b;
  } else if (a > b) {
    a = b;
  }
  return a;
}

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

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const ll inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 998244353;
const ll max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

ll w[55], p[55], fact[55];
ll dp[55][55][55];

ll qpow(ll x, ll v) {
  x = x % mod;
  ll y = 1;
  while (v) {
    if (v & 1) y = y * x % mod;
    x = x * x % mod;
    v >>= 1;
  }
  return y;
}
ll inv(ll x) { return qpow(x, mod - 2); }

ll dfs(ll n, ll m, ll k) {
  ll& ret = dp[n][m][k];
  if (ret != -1) {
    return ret;
  }

  if (n < m || k < m || (k > 0 && m == 0)) {  // 非法数据
    ret = 0;
  } else if (m == 0 && k == 0) {  // 不抽奖
    ret = 1;
  } else {
    ll ans = 0;
    FOR1(i, 0, k - m + 1) {
      ll tmp = inv(fact[i]) * qpow(p[n], i) % mod;
      // printf("n=%lld m=%lld k=%lld i=%lld tmp=%lld\n", n, m, k, i, tmp);
      if (i == 0) {
        ans += dfs(n - 1, m, k) * tmp;
      } else {
        ans += dfs(n - 1, m - 1, k - i) * tmp;
      }
      ans %= mod;
    }
    ret = ans;
  }

  // printf("n=%lld m=%lld k=%lld ret=%lld\n", n, m, k, ret);
  return ret;
}

int main() {
  ll n, m, k;
  scanf("%lld%lld%lld", &n, &m, &k);
  ll sum = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &w[i]);
    sum += w[i];
  }
  for (int i = 1; i <= n; i++) {
    p[i] = w[i] * inv(sum) % mod;
    // printf("i=%d f=%lld\n", i, p[i]);
  }

  fact[0] = 1;
  for (int i = 1; i <= k; i++) {
    fact[i] = (fact[i - 1] * i) % mod;
    // printf("i=%d f=%lld\n", i, fact[i]);
  }

  memset(dp, -1, sizeof(dp));
  printf("%lld\n", dfs(n, m, k) * fact[k] % mod);
  return 0;
}
