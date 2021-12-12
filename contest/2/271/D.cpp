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

typedef long long ll;

#define myprintfex(format, args...) printf(format, ##args)
// #define myprintfex(format, args...)

class Solution {
    // [positioni, amounti]
    void UpdateNums(vector<vector<int>>& nums, int startPos){
        for(auto&v: nums) {
            if(v[0] == startPos) {
                return ;
            }
        }
        
        // vector<int> target;
        // target.push_back(startPos);
        // target.push_back(0);
        nums.push_back({startPos, 0});
        
        sort(nums.begin(), nums.end());
    }
    
    int ans = 0;
    vector<int> index;
    vector<int> preSum;
    int n;
    
    void tryLeftFirst(int startPos, int k){
        int centerIndex = lower_bound(index.begin(), index.end(), startPos) - index.begin();
        for(int i = centerIndex; i >= 0; i--) {
            // 从 center 先到 i，再向右走
            int leftDis = index[centerIndex] - index[i];
            if(leftDis > k) {
                break; // 走不到了
            }
            
            int tmpAns = preSum[centerIndex + 1] - preSum[i];
            
            // 可以再走回来
            int leftK = k - leftDis * 2;
            int rightIndex = centerIndex;
            if(leftK > 0 && centerIndex != n - 1) {
                int rightPos = startPos + leftK;
                auto it = lower_bound(index.begin(), index.end(), rightPos);
                if(it == index.end() || *it > rightPos) {
                    it--;
                }
                
                int rightIndex = it - index.begin();
                if(rightIndex > centerIndex) {
                    tmpAns += preSum[rightIndex + 1] - preSum[centerIndex + 1];
                }
            }
            
            ans = max(ans, tmpAns);
        }
    }
    
    void tryRightFirst(int startPos, int k){
        int centerIndex = lower_bound(index.begin(), index.end(), startPos) - index.begin();
        
        for(int i = centerIndex; i < n; i++) {
            int rightDis = index[i] - index[centerIndex];
            if(rightDis > k) {
                break;
            }
            
            int tmpAns = preSum[i + 1] - preSum[centerIndex];
            // 可以再走回来
            int leftK = k - rightDis * 2;
            int leftIndex = centerIndex;
            if(leftK > 0 && centerIndex != 0) {
                int leftPos = startPos - leftK;
                auto it = lower_bound(index.begin(), index.end(), leftPos);
                int leftIndex = it - index.begin();
                if(centerIndex > leftIndex) {
                    tmpAns += preSum[centerIndex] - preSum[leftIndex];
                }
                
            }
            
            
            ans = max(ans, tmpAns);
        }
    }
    
public:
    int maxTotalFruits(vector<vector<int>>& nums, int startPos, int k) {
        UpdateNums(nums, startPos);
        
        n = nums.size();
        
        index.reserve(n);
        for(auto&v: nums) {
            index.push_back(v[0]);
        }
        
        preSum.resize(n + 1, 0);  
        for(int i = 1; i <= n; i++) {
            preSum[i] = preSum[i-1] + nums[i-1][1];
        }
        
        tryLeftFirst(startPos, k);
        tryRightFirst(startPos, k);
        
       
        return ans;
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
