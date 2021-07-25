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
// 排序，小于是升序：[](auto&a, auto&b){ return a < b; })
// 优先队列 priority_queue<Node>：大于是升序
// __builtin_popcount 快速得到 1 的个数
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


int dp[1024];

class Solution {
    vector<int> students;
    vector<int> mentors;
    int n;
    int maxBit;
    
    int MatchScore(int bit, int offset){
        int val = students[bit] ^ mentors[offset];
        return n - __builtin_popcount(val);
    }
    
    int Dfs(const int mast, const int offset){
        if(offset == maxBit) {
            return 0;
        }
        if(dp[mast] != -1) {
            return dp[mast];
        }
        
        int ans = 0;
        // select one bit vs offset
        for(int bit = 0; bit < maxBit; bit++) {
            if((mast & (1<<bit)) == 0) continue;
            //printf("0: mast=%d offset=%d bit=%d child=%d ans=%d\n", mast, offset, bit, mast ^ (1<<bit), ans);
            ans = max(ans, MatchScore(bit, offset) + Dfs(mast ^ (1<<bit), offset + 1));
            //printf("1: mast=%d offset=%d bit=%d child=%d ans=%d\n", mast, offset, bit, mast ^ (1<<bit), ans);
        }
        
        return dp[mast] = ans;
    }
public:
    int maxCompatibilitySum(vector<vector<int>>& students_, vector<vector<int>>& mentors_) {
        maxBit = students_.size();
        n = students_[0].size();
        
        students.reserve(maxBit);
        mentors.reserve(maxBit);
        
        for(auto& l: students_) {
            int mast = 0;
            for(int i=0;i<n;i++){
                mast |= l[i]<<i;
            }
            students.push_back(mast);
        }
        
        for(auto& l: mentors_) {
            int mast = 0;
            for(int i=0;i<n;i++){
                mast |= l[i]<<i;
            }
            mentors.push_back(mast);
        }
        
        memset(dp, -1, sizeof(dp));
        int mast = (1 << maxBit) - 1;
        //printf("maxBit=%d n=%d maxMast=%d\n", maxBit, n, mast);
        return Dfs(mast, 0);
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
