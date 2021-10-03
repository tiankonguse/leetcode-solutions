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


class Solution {
    // Alice 选择了
    bool DfsBob(const int sum, int dp[3]){
        if(dp[0] == 0 && dp[1] == 0 && dp[2] == 0) return true;
        for(int i = 0; i < 3; i++) {
            if(dp[i] > 0 && (sum + i) % 3 != 0){
                // printf("check bob: sum=%d a=%d b=%d c=%d i=%d ", sum,  dp[0], dp[1], dp[2], i);
                dp[i]--;
                if(!DfsAlice(sum + i, dp)) {
                    dp[i]++;
                    // printf(" win\n");
                    return true;
                }
                // printf(" lose\n");
                dp[i]++;
            }
        }
        return false;
        
    }
    
    bool DfsAlice(const int sum, int dp[3]){
        if(dp[0] == 0 && dp[1] == 0 && dp[2] == 0) return false;
        
        for(int i = 0; i < 3; i++) {
            if(dp[i] > 0 && (sum + i) % 3 != 0){
                // printf("check alice: sum=%d a=%d b=%d c=%d i=%d ", sum,  dp[0], dp[1], dp[2], i);
                dp[i]--;
                if(!DfsBob(sum + i, dp)) {
                    dp[i]++;
                    // printf(" win\n");
                    return true;
                }
                // printf(" lose\n");
                dp[i]++;
            }
        }
        return false;
    }
public:
    bool stoneGameIX(vector<int>& stones) {
        int dp[3] = {0, 0, 0};
        for(auto v: stones) {
            dp[v % 3]++;
        }
        
        // printf("a=%d b=%d c=%d\n", dp[0], dp[1], dp[2]);
        
        dp[0] = dp[0] % 2;
        while(dp[1] > 2 && dp[2] > 2) {
            dp[1]--, dp[2]--;
        }
        
        // printf("a=%d b=%d c=%d\n", dp[0], dp[1], dp[2]);
        return DfsAlice(0, dp);
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
