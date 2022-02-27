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

typedef long long ll;
ll& myMin(ll& a, ll b) {
  if (a < 0) {
    a = b;
  } else if (a > b) {
    a = b;
  }
  return a;
}

const int MaxBit = 33;
vector<ll> dpAll;
vector<ll> loopMin;

class Solution {
    int changeTime;
    
    ll DfsAll(int n){
        if(dpAll[n] != -1) return dpAll[n];
        //printf("dfs n = %d\n", n);
 
        ll& ans = dpAll[n];
        if(n < MaxBit && loopMin[n] != -1) {
            ans = loopMin[n]; // 不切换
            //printf("n=%d all=%lld\n", n, ans);
        }
        
        // 如果 ans == -1, 必须切换
        int maxi = min(MaxBit, n);
        for(int i = 1; i < maxi; i++) {
            if(loopMin[i] == -1) break; // 之后的无解
            
            ll tmp = DfsAll(n - i);
            ll newans = loopMin[i] + changeTime + DfsAll(n - i);
            if(ans == -1 || ans > newans) {
                ans = newans;
                //printf("n=%d update i=%d select=%lld next=%lld ans=%lld\n", n, i, loopMin[i], tmp, ans);   
            } 
            
        }
        return ans;
    }
    
public:
    int minimumFinishTime(vector<vector<int>>& tires, int changeTime_, int numLaps) {
        changeTime = changeTime_;
        
        ll min32 = 1LL << 32;
        
        loopMin.clear();
        loopMin.resize(MaxBit, -1);
        for(auto& p: tires) {
            ll f = p[0], r = p[1];
            ll sum = 0;
            for(int i = 1; i < MaxBit; i++) {
                sum += f;
                if(sum > min32) {
                    break;
                }
                myMin(loopMin[i], sum);
                //printf("[%lld, %lld] i=%d f=%lld sum=%lld\n", f, r, i, f, loopMin[i]);
                f = f * r;
            }
        }
        
        dpAll.clear();
        dpAll.resize(numLaps+1, -1);
        
        return DfsAll(numLaps);
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
