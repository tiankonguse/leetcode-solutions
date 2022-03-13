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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

__int128_t g[max6];
__int128_t sum[max6];

void Init() {
  memset(g, 0, sizeof(g));
  memset(sum, 0, sizeof(sum));
  g[1] = 1;
  sum[1] = 1;

  for (int x = 2; x < max6; x++) {
    int y = sqrt(x * 1.0);
    g[x] = sum[y];
    sum[x] = sum[x - 1] + g[x];
  }
}

__int128_t mysqrt(__int128_t x) {
  __int128_t l = 1, r = sqrt(x * 1.0) * 2;
  while (l < r) {  // (l, r)
    __int128_t mid = (l + r) / 2;
    if (mid * mid > x) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return l - 1;
}

ull Solver(__int128_t x) {
  __int128_t ans = 0;
  __int128_t y = mysqrt(x);  // 1 ~ y

  while (y > 0) {
    __int128_t yy = mysqrt(y);
    __int128_t yy2 = yy * yy;
    // printf("y=%llu yy=%llu yy2=%llu add=%llu num=%llu g=%llu\n", y, yy, yy2,
    //        (y - yy2 + 1) * g[yy], (y - yy2 + 1), g[yy]);
    ans += (y - yy2 + 1) * sum[yy];
    y = yy2 - 1;
  }

  return ans;
}

int main() {
  int t;
  Init();

  // ull MAX_VAL = 9;
  // for (int i = 1; i <= 18; i++) {
  //   MAX_VAL = MAX_VAL * 10;
  // }
  // ull a = MAX_VAL;
  // ull a9 = a;
  // ull b = sqrt(a * 1.0);
  // ull c = sqrt(b * 1.0);
  // printf("a=%llu b=%llu c=%llu\n", a, b, c);
  // printf("a=%llu sqrt=%llu mysqrt=%llu\n", a9, ull(sqrt(a9)),
  // ull(mysqrt(a9))); printf("a=%llu sqrt+eps=%llu mysqrt=%llu\n", a9-1,
  // ull(sqrt(a9-1)), ull(mysqrt(a9-1))); printf("a=%llu sqrt=%llu
  // mysqrt=%llu\n", a9-1, ull(sqrt(a9-1)), ull(mysqrt(a9-1))); printf("%llu\n",
  // Solver(MAX_VAL));

  scanf("%d", &t);
  while (t--) {
    ull x;
    scanf("%llu", &x);
    printf("%llu\n", Solver(x));
  }

  return 0;
}
