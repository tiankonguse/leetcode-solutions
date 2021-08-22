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


class Solution {
    vector<int> ans;
    map<int, int> m;
    int zheng = 0, zero = 0, fu = 0;
    
    void Del(int k){
        m[k]--;
        if(m[k] == 0) {
            m.erase(k);
        }
    }
    int GetMin(){
        return m.begin()->first;
    }
    int GetMax(){
        return m.rbegin()->first;
    }
    
vector<int>& FastZheng(int n){
    Del(0); // 删除空集

    vector<int> pre; // 保存的子集和
    pre.reserve(1<<n);
    pre.push_back(0);

    while(!m.empty()) {
        int one = GetMin();
        zheng--;
        for(auto v: pre) {
            Del(v + one);
            pre.push_back(v + one);
        }
        ans.push_back(one);
    }
    return ans;
}
    
    vector<int>& FastFu(int n){
        Del(0); // 删除空集
        
        vector<int> pre;
        pre.reserve(1<<n);
        pre.push_back(0);
        
        while(!m.empty()) {
            int one = GetMax();
            fu--;
            for(auto v: pre) {
                Del(v + one);
                pre.push_back(v + one);
            }
            ans.push_back(one);
        }
        return ans;
    }
    
    void TryZheng(int zheng_num){
        
    }
    
    vector<int>& ZhengFu(int n){
        int fu_num = log2(fu * 1.0);
        int zheng_num = log2(zheng * 1.0);
        if(fu_num > zheng_num) {
            TryZheng(zheng_num);
        }else {
            TryFu(fu_num);
        }
        
        if(fu == 0) {
            return FastZheng(n);
        }
        if(zheng == 0) {
            return FastFu(n);
        }
        
        return ans;
    }
    
public:
    vector<int> recoverArray(int n, vector<int>& sums) {
        for(auto v: sums) {
            if(v == 0) {
                zero ++;
            }else if( v > 0) {
                zheng++;
            } else if(v < 0) {
                fu++;
            }
            m[v]++;
        }
        

        
        
        // 正负混合场景：
        // 方法：每次找两个最小值即可
        return ZhengFu(n);
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
