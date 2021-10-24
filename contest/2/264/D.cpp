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


struct Node{
    Node(){
        preNum = 0;
        startTime = -1;
        cost = 0;
    }
    int preNum;
    vector<int> nexts;
    int startTime;
    int cost;
};

class Solution {
    vector<Node> nodes;
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        nodes.resize(n+2);
        
        for(int i=1;i<=n;i++) {
            nodes[i].cost = time[i-1];
            
        }
        
        for(auto&p: relations) {
            int u = p[0], v = p[1];
            nodes[u].nexts.push_back(v);
            nodes[v].preNum++;
        }
        
        nodes[0].nexts.reserve(n);
        nodes[n+1].nexts.reserve(n);
        for(int i = 1; i <= n; i++) {
            if(nodes[i].preNum == 0) {
                nodes[0].nexts.push_back(i);
                nodes[i].preNum++;
            }
            nodes[i].nexts.push_back(n+1);
            nodes[n+1].preNum++;
        }
        
        queue<int> que;
        nodes[0].startTime = 0;
        que.push(0);
        while(!que.empty()) {
            int now = que.front(); que.pop();
            auto& nowNode = nodes[now];
            for(auto v: nowNode.nexts) {
                nodes[v].preNum--;
                
                int newStartTime = nowNode.startTime + nowNode.cost;
                if(nodes[v].startTime < newStartTime){
                    nodes[v].startTime = newStartTime;
                }
                if(nodes[v].preNum == 0) {
                    que.push(v);
                }
            }
            
        }
        
        
        return nodes[n+1].startTime;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
