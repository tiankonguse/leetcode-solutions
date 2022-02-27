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

map<ll, set<ll>> mxy;
map<ll, set<ll>> myx;

set<pair<ll, ll>> flag;

ll sx, sy, gx, gy;
ll ans = 0;

struct Node {
  Node(ll x = 0, ll y = 0, int num = 0) : x(x), y(y), num(num) {}
  ll x, y;
  int num;
};
queue<Node> que;

// lower_bound 大于等于
// upper_bound 大于

void Up(Node& now) {
  ll x = now.x, y = now.y;
  int num = now.num;
  //向上, y 不变，x 变小
  if (myx.count(y) == 0) {
    return;
  }

  const auto& s = myx[y];
  auto it = s.lower_bound(x);
  if (it == s.begin()) {
    return;
  }

  it--;  // 上一个障碍物
  LL X = *it + 1, Y = y;
  if (X == x && Y == y) {
    return;
  }
  if (X == gx && Y == gy) {
    ans = num + 1;
  }

  if (flag.count({X, Y}) == 0) {
    flag.insert({X, Y});
    que.push(Node(X, Y, num + 1));
  }
}

void Down(Node& now) {
  ll x = now.x, y = now.y;
  int num = now.num;
  //向下， y 不变，x 变大
  if (myx.count(y) == 0) {
    return;
  }

  const auto& s = myx[y];
  auto it = s.upper_bound(x);
  if (it == s.end()) {
    return;
  }

  // it--;  // 上一个障碍物
  LL X = *it - 1, Y = y;
  if (X == x && Y == y) {
    return;
  }
  if (X == gx && Y == gy) {
    ans = num + 1;
  }

  if (flag.count({X, Y}) == 0) {
    flag.insert({X, Y});
    que.push(Node(X, Y, num + 1));
  }
}
void Left(Node& now) {
  ll x = now.x, y = now.y;
  int num = now.num;
  //向左， x 不变，y 变小
  if (mxy.count(x) == 0) {
    return;
  }

  const auto& s = mxy[x];
  auto it = s.lower_bound(y);
  if (it == s.begin()) {
    return;
  }

  it--;  // 上一个障碍物
  LL X = x, Y = *it + 1;
  if (X == x && Y == y) {
    return;
  }
  if (X == gx && Y == gy) {
    ans = num + 1;
  }

  if (flag.count({X, Y}) == 0) {
    flag.insert({X, Y});
    que.push(Node(X, Y, num + 1));
  }
}
void Right(Node& now) {
  ll x = now.x, y = now.y;
  int num = now.num;
  //向右， x 不变，y 变大
  if (mxy.count(x) == 0) {
    return;
  }

  const auto& s = mxy[x];
  auto it = s.upper_bound(y);
  if (it == s.end()) {
    return;
  }

  // it--;  // 上一个障碍物
  LL X = x, Y = *it - 1;
  if (X == x && Y == y) {
    return;
  }

  if (X == gx && Y == gy) {
    ans = num + 1;
  }

  if (flag.count({X, Y}) == 0) {
    flag.insert({X, Y});
    que.push(Node(X, Y, num + 1));
  }
}

ll Solver() {
  que.push(Node(sx, sy, 0));

  ans = -1;
  while (!que.empty()) {
    Node now = que.front();
    que.pop();
    Up(now);
    Down(now);
    Left(now);
    Right(now);
    if (ans != -1) {
      return ans;
    }
  }

  return -1;
}
int main() {
  ll h, w;
  ll n;

  scanf("%lld%lld%d", &h, &w, &n);
  scanf("%lld%lld", &sx, &sy);
  scanf("%lld%lld", &gx, &gy);

  for (int i = 0; i < n; i++) {
    ll x, y;
    scanf("%lld%lld", &x, &y);
    mxy[x].insert(y);
    myx[y].insert(x);
  }

  printf("%lld\n", Solver());

  return 0;
}
