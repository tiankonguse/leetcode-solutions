#include "base.h"

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

// int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
// int dir[8][2] = {{0,1},{1, 1},{1,0},{1,-1}, {0,-1}, {-1, -1}, {-1,0}, {-1, 1}};
// lower_bound 大于等于
// upper_bound 大于
// vector/array: upper_bound(vec.begin(), vec.end(), v)
// map: m.upper_bound(v)
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);
// unordered_map / unordered_set
// __builtin_popcount 一的个数
// size_t found=str.find(char/char*/string); std::string::npos
// 排序，小于是升序：[](auto&a, auto&b){ return a < b; })
// 优先队列 priority_queue<Node>：大于是升序
// struct Node{
//     int t;
//     bool operator<(const Node & that)const { return this->t > that.t; }
// };

// mutex mtx;       // 互斥量，锁，定义一个即可
// condition_variable cv; // 条件变量
// cv.notify_one(); // 事件通知
// unique_lock<mutex> lck(mtx); 
// cv.wait(lck); //等待事件

// atomic_int tick; // 原子计数
// this_thread::yield();  // 线程 sleep

// #include <semaphore.h> // 需要手动包含信号量头文件
// sem_t sem_done;
// sem_init(&bar_done, 0 , 1);
// sem_wait(&bar_done);
// sem_post(&foo_done);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;


typedef long long ll;
const int N = 10000;
class Solution {
    int n , m;
    ll minVal;
    ll maxVal;
    
    vector<ll> nums;
    vector<ll> sumVal, sumNum;
    
    int Abs(int a){
        return a < 0 ? -a : a;
    }
    bool  Check(vector<vector<int>>& grid, int x) {
        maxVal = minVal = grid[0][0];
        
        nums.resize(N + 1);
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                const ll val = grid[i][j];
                if(Abs(minVal - val) % x != 0) {
                    return false;
                }
                minVal = min(val, minVal);
                maxVal = max(val, maxVal);
                nums[val]++;
                // printf("i=%d j=%d v=%lld num=%lld\n", i, j, val, nums[val]);
            }
        }
        
        sumNum.resize(N + 1, 0);
        sumVal.resize(N + 1, 0);
        // printf("minVal=%lld maxVal=%lld\n", minVal, maxVal);
        for(int i = minVal; i <= maxVal; i ++) {
            sumNum[i] = sumNum[i-1] + nums[i];
            sumVal[i] = sumVal[i-1] + i * nums[i];
            // printf("v=%d num=%lld preNum=%lld preSUm=%lld\n", i, nums[i], sumNum[i], sumVal[i]);
        }
        
        return true;
    }
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        n = grid.size();
        m = grid[0].size();
        
        if(!Check(grid, x)) {
            return -1;
        }
        
        // printf("minVal = %lld\n", minVal);
        ll ans = ((sumVal[maxVal] - sumVal[minVal]) - (sumNum[maxVal] - sumNum[minVal]) * minVal) / x;
        // printf("ans minval = %lld\n", ans);
        
        for(int i = minVal; i <= maxVal; i += x) {
            ll tmp = 0;
            
            tmp += (sumNum[i-1] * i - sumVal[i-1]) / x;
            tmp += ((sumVal[maxVal] - sumVal[i]) - (sumNum[maxVal] - sumNum[i]) * i) / x;
            
            if(tmp < ans) {
                ans = tmp;
            }
            
        }
        
        return ans;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
