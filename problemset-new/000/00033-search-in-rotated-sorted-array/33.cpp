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

vector / array : upper_bound(vec.begin(), vec.end(), v)
map: m.upper_bound(v)

区间 [l,r]内满足的个数：
std::distance(v.begin(), it)
map/set distance 复杂度 O(N)
vector/数组 distance 复杂度 O(1)

upper_bound(vec.begin(), vec.end(), r) - lower_bound(vec.begin(), vec.end(), l);



反转 reverse(v.begin(), v.end())


sum = accumulate(a.begin(), a.end(), 0ll);

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

class Solution {
  int searchMax(vector<int>& nums) {
    if (nums.front() < nums.back()) {
      return nums.size() - 1;  // 正常顺序
    }

    int l = 0, r = nums.size() - 1;
    while (l < r) {  // [l, r]
      int m = (l + r + 1) / 2;
      if (nums[m] <= nums.back()) {
        r = m - 1;
      } else {
        l = m;
      }
    }
    return l;
  }

 public:
  int search(vector<int>& nums, int t) {  //
    if (nums.size() == 1) {
      if (nums[0] == t) {
        return 0;
      } else {
        return -1;
      }
    }

    int m = searchMax(nums);

    // printf("max pos=%d\n", m);
    int l = 0, r = nums.size() - 1;

    if (nums.front() > t) {
      l = m + 1;
    } else {
      r = m;
    }

    while (l <= r) {  // [l, r]
      int m = (l + r) / 2;
    //   printf("l=%d r=%d m=%d\n", l, r, m);
      int v = nums[m];
      if (v == t) {
        // printf("m=%d\n", m);
        return m;
      }
      if (v < t) {
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
    // printf("no ans\n");
    return -1;
  }
};

int main() {
  int ans = 1;
  vector<int> nums = {3, 1};
  int t = 1;
  TEST_SMP2(Solution, search, ans, nums, t);

  return 0;
}
