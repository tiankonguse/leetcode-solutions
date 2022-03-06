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
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

ll nums[max6];

void Init() {
  nums[0] = 1;
  nums[1] = 26;
  for (int i = 2; i < max6; i++) {
    nums[i] = (nums[i - 2] * 26) % mod;
  }
}

char str[max6];
string str2;

ll Solver(int n) {
  ll ans = 0;

  str2 = str;

  int l = 0, r = n - 1;
  while (l <= r) {
    for (char c = 'A'; c < str[l]; c++) {
      ans = (ans + nums[max(r - l - 1, 0)]) % mod;
    }
    str2[r] = str2[l] = str[l];
    if (l == r || l + 1 == r) {
      if (str2 <= str) {
        ans = (ans + 1) % mod;
      }
    }
    l++, r--;
  }

  return ans;
}

int main() {
  Init();
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%s", &n, str);
    printf("%lld\n", Solver(n));
  }

  return 0;
}
