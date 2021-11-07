#include "base.h"

#define myprintf(format, args...) printf("line[%s]" format, __LINE__, ##args)
#define myprintf(format, args...)

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


#define myprintf(format, args...) printf(format, ##args)
#define myprintf(format, args...)

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

class Solution {
    vector<vector<pair<int, int>>> path;
    vector<int> minTime;
    int n;
    int maxTime;
    int ans;
    
    void CalMinStep(){
        minTime.resize(n, -1);
        minTime[0] = 0;
        
        min_queue<pair<int, int>> que;
        que.push({0, 0});
        
        while(!que.empty()) {
            auto p = que.top(); que.pop();
            int u = p.second, t = p.first;
            
            if(t != minTime[u]) continue; // 有更优的路径了,这个忽略掉
            
            for(auto&p: path[u]) {
                int v = p.first, c = p.second;
                
                
                if(minTime[v] == -1) {
                    minTime[v] = t + c;
                    que.push({minTime[v], v});
                } else if(minTime[v] > t + v){
                    minTime[v] = t + c;
                    que.push({minTime[v], v});
                }
            }
        }
        
        for(int i = 0; i < n; i ++) {
            myprintf("i=%d minTime=%d\n", i, minTime[i]);
        }
        
    }
    
    
    vector<int> flag;
    vector<int> values;
    void Dfs(int u, int t, int tmpAns){
        if(t + minTime[u] > maxTime) return; // 剪枝
        
        if(u == 0) {
            ans = max(ans, tmpAns);
        }
        
        for(auto& p: path[u]) {
            int v = p.first, c= p.second;
            flag[v]++;
            
            int tmpAns2 = tmpAns;
            if(flag[v] == 1) {
                tmpAns2 += values[v];
            }
            Dfs(v, t + c, tmpAns2);
            
            flag[v]--;
        }
    }
    
public:
    int maximalPathQuality(vector<int>& values_, vector<vector<int>>& edges, int maxTime_) {
        maxTime = maxTime_;
        values.swap(values_);
        
        n = values.size();
        
        path.resize(n);
        for(auto& p: edges) {
            int u = p[0], v = p[1], t = p[2];
            path[u].push_back({v, t});
            path[v].push_back({u, t});
        }
        
        
        CalMinStep();
        
        ans = 0;
        flag.resize(n, 0);
        flag[0]++;
        Dfs(0, 0, values[0]);
        return ans;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
