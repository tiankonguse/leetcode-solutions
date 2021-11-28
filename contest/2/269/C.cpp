#include "base.h"

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

/*
int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

int dir[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};

lower_bound 大于等于
upper_bound 大于

vector / array : upper_bound(vec.begin(), vec.end(), v)
map: m.upper_bound(v)

区间 [l,r]内满足的个数：
upper_bound(vec.begin(), vec.end(), r) - lower_bound(vec.begin(), vec.end(), l);
std::distance(v.begin(), it)

vector预先分配内存 reserve
反转 reverse(v.begin(), v.end())


sum = accumulate(a.begin(), a.end(), 0);
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

class Solution {
    vector<int> nums;
    int n;
    int minPos, maxPos;
    
    void findMinMaxPos(){
        minPos = 0, maxPos = 0;
        for(int i = 0; i < n; i++) {
            if(nums[minPos] > nums[i]) {
                minPos = i;
            }
            if(nums[maxPos] < nums[i]) {
                maxPos = i;
            }
        }
    }
    
    int LeftFirst(){
        int ans = 0;
        int l = 0, r = n - 1;
        
        ans += minPos - l + 1;
        l = minPos + 1;
        
        ans += min(maxPos - l + 1, r - maxPos + 1);
        return ans;
    }
    
    int RightFirst() {
        int ans = 0;
        int l = 0, r = n - 1;
        
        ans += r - maxPos + 1;
        r = maxPos - 1;
        
        ans += min(minPos - l + 1, r - minPos + 1);
        return ans;
    }
    
public:
    int minimumDeletions(vector<int>& nums_) {
        nums.swap(nums_);
        n = nums.size();
        
        findMinMaxPos();
        
        if(minPos > maxPos) {
            swap(minPos, maxPos);
        }
        
        return min(LeftFirst(), RightFirst());
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  priority_queue<Node> que;
  que.push(Node(1));
  que.push(Node(2));
  while (!que.empty()) {
    printf("val:%d\n", que.top().t);
    que.pop();
  }

  return 0;
}
