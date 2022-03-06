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

int nums1[max4], nums2[max4];
int nums11[max4], nums22[max4];
map<int, int> m1, m2;
int n;

void Step1(int* nums, int p) {
  int &x = nums[p - 2], &y = nums[p - 1], &z = nums[p];
  int tmp = z;
  z = y;
  y = x;
  x = tmp;
}

void Sort1(int n, int* nums) {
  for (int i = 0; i < n - 2; i++) {  // n-3, n-2, n-1
    int minPos = i;
    for (int j = i; j < n; j++) {
      if (nums[j] < nums[minPos]) {
        minPos = j;
      }
    }

    while (i + 2 <= minPos) {  // i, i+1, i+2 后面
      Step1(nums, minPos);
      minPos -= 2;
    }

    if (i + 1 == minPos) {
      Step1(nums, minPos + 1);
      Step1(nums, minPos + 1);
    }
  }
}

void Step2(int* nums, int p) {
  int &x = nums[p - 2], &y = nums[p - 1], &z = nums[p];
  int tmp = x;
  x = y;
  y = z;
  z = tmp;
}
void Sort2(int n, int* nums) {
  for (int i = 0; i < n - 2; i++) {
    int minPos = i;
    for (int j = i; j < n; j++) {
      if (nums[j] < nums[minPos]) {
        minPos = j;
      }
    }

    while (i + 2 <= minPos) {  // i, i+1, i+2 后面
      Step2(nums, minPos);
      minPos -= 1;
    }

    if (i + 1 == minPos) {
      Step2(nums, minPos + 1);
    }
  }
}

typedef void(SortFun)(int, int*);

bool CheckEx(int* nums1, int* nums2, SortFun* sortFun1, SortFun* sortFun2) {
  for (int i = 0; i < n; i++) {
    nums11[i] = nums1[i];
    nums22[i] = nums2[i];
  }
  sortFun1(n, nums11);
  sortFun2(n, nums22);

  for (int i = 0; i < n; i++) {
    if (nums11[i] != nums22[i]) {
      return false;
    }
  }

  return true;
}

bool Check() {
  if (m1.size() != m2.size()) return false;

  for (auto p : m1) {
    int k = p.first, v = p.second;
    if (m2.count(k) == 0) return false;
    if (m2[k] != v) return false;
  }

  for (auto p : m1) {
    if (p.second == 2) return true;
  }

  // if (CheckEx(nums1, nums2, Sort1, Sort1)) {
  //   return true;
  // }
  // if (CheckEx(nums1, nums2, Sort2, Sort2)) {
  //   return true;
  // }
  if (CheckEx(nums1, nums2, Sort1, Sort2)) {
    return true;
  }
  // if (CheckEx(nums1, nums2, Sort2, Sort1)) {
  //   return true;
  // }

  return false;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums1[i]);
    m1[nums1[i]]++;
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums2[i]);
    m2[nums2[i]]++;
  }

  printf("%s\n", Check() ? "Yes" : "No");

  return 0;
}
