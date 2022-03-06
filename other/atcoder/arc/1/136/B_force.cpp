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

string Next(string s, int p) {
  char &x = s[p - 2], &y = s[p - 1], &z = s[p];
  char tmp = z;
  z = y;
  y = x;
  x = tmp;
  return s;
}
int A(int n) {
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    ans *= i;
  }
  return ans;
}

void Solver(int n, int pos = 0) {
  string str;
  for (int i = 1; i <= n; i++) {
    str.push_back('a' + i);
  }
  // str[pos] = str.front();

  set<string> s;
  vector<string> que;
  que.push_back(str);
  s.insert(str);

  while (!que.empty()) {
    str = que.back();
    que.pop_back();

    for (int i = 2; i < str.size(); i++) {
      string tmp = Next(str, i);
      // printf("str=%s i=%d next=%s\n", str.c_str(), i, tmp.c_str());
      if (s.count(tmp)) continue;
      que.push_back(tmp);
      s.insert(tmp);
    }
  }

  printf("n=%d ans=%d A=%d\n", n, s.size(), A(n));

  // for (auto str : s) {
  //   printf("%s\n", str.c_str());
  // }
}

int main() {
  // Solver(4);
  for (int i = 3; i <= 26; i++) {
    // for (int j = 1; j < i; j++) {
    Solver(i, 0);
    // }
  }

  return 0;
}
