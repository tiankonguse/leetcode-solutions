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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 998244353;
const int max3 = 2555, max4 = 11100, max5 = 200100, max6 = 2000100;

ll dp[55][55];
ll cab[max3][max3];

ll C(int a, int b) {
  ll& ret = cab[a][b];
  if (ret != -1) {
    return ret;
  }

  if (a < b) {
    return ret = 0;
  }

  if (a == b || b == 0) {
    return ret = 1;
  }

  return ret = (C(a - 1, b) + C(a - 1, b - 1)) % mod;
}

int main() {
  int n, m, b, w;
  scanf("%d%d%d%d", &n, &m, &b, &w);

  memset(cab, -1, sizeof(cab));

  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = C(i * j, b);
      for (int x = 1; x <= i; x++) {
        for (int y = 1; y <= j; y++) {
          if (x == i && y == j) continue;
          ll xy = dp[x][y] * C(i, x) % mod * C(j, y) % mod;
          dp[i][j] = (dp[i][j] - xy + mod) % mod;
        }
      }

      ll ni = n - i;
      ll mj = m - j;
      ll ij = dp[i][j] * C(n, i) % mod * C(m, j) % mod;
      ans = (ans + ij * C(ni * mj, w) % mod) % mod;
    }
  }
  printf("%lld\n", ans);

  return 0;
}
