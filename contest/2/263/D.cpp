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


vector<int> step;
struct Node{
    int t;
    int u;
    Node(int t = 0, int u = 0):t(t), u(u){}
    bool operator<(const Node& that)const {
        if(this->t != that.t) {
            return this->t > that.t; 
        }
        return step[this->u] > step[that.u];
    }
};

class Solution {
    vector<vector<int>> path;
    vector<int> minEdges;
    int n;
    vector<int> ans;
    int time, change;
    vector<int> stepToTime;
    vector<int> flag;

    
    void BfsStep(){
        step.clear();
        step.resize(n+1, -1);
        
        queue<int> que;
        que.push(n);
        step[n] = 0;
        
        while(!que.empty()){
            int u = que.front();que.pop();
            for(int v: path[u]) {
                if(step[v] != -1) continue;
                
                
                que.push(v);
                step[v] = step[u] + 1;
            }
        }
        
        
    }
    
    void UpdateAns(int t){
        for(auto v: ans) {
            if(v == t) return; // 重复值
        }
        
        ans.push_back(t);
        for(int i = ans.size() - 1; i > 0; i--){
            if(ans[i] < ans[i - 1]) { // 冒泡
                swap(ans[i], ans[i-1]);
            }
        }
        
        if(ans.size() == 3) {
            ans.pop_back();
        }
        
    }
    
    int GetSecondAns(){
        if(ans.size() != 2) {
            return -1;
        }
        return ans.back();
    }
    
    int GetFirstAns(){
        if(ans.size() == 0) {
            return -1;
        }
        return ans.front();
    }
    
    void InitStepTime(){
        stepToTime.resize(n+2, 0);
        int t = 0;
        for(int i = 0; i <= n; i++) {
            if((t / change) % 2 == 1) {
                // 等待到绿灯
                t += change - (t % change);
            }
            t += time; // 赶路时间
            stepToTime[i+1] = t;
        }
    }
    
    void CalTmpAns(){
        
        // first ans 是最短路
        int s = step[1];
        // printf("s=%d\n", s);
        int t = 0;
        for(int i = 0; i < s; i++) {
            if((t / change) % 2 == 1) {
                // 等待到绿灯
                t += change - (t % change);
            }
            t += time; // 赶路时间
        }
        
        UpdateAns(t);
        // printf("first t = %d\n", t);
        
        // 次优答案是回去一次再过来
        for(int i = 0; i < 2; i++) {
            if((t / change) % 2 == 1) {
                // 等待到绿灯
                t += change - (t % change);
            }
            t += time; // 赶路时间
        }
        UpdateAns(t);
        // printf("second t = %d\n", t);
    }
    
    bool Skip(int v, int t){
        if((t / change) % 2 == 1) {
            // 等待到绿灯
            t += change - (t % change);
        }
        return t + stepToTime[step[v]] >= GetSecondAns();
    }
    
public:
    int secondMinimum(int n_, vector<vector<int>>& edges, int time_, int change_) {
        change = change_;
        time = time_;
        n = n_;
        
        path.resize(n + 1);
        flag.resize(n+1, 0);
        for(auto& e: edges) {
            int u = e[0], v = e[1];
            path[u].push_back(v);
            path[v].push_back(u);
        }
        
        BfsStep();
        
        CalTmpAns(); // 计算临时次优答案，用于剪枝
        InitStepTime(); //
        
        priority_queue<Node> que; // 队列的时间为到达时间
        que.push(Node{0, 1});
        
        while(!que.empty()) {
            Node p = que.top(); que.pop();
            int u = p.u;
            int t = p.t;
            // printf("t=%d u=%d\n", t, u);
            // 修正对齐 t 时间
            if((t / change) % 2 == 1) {
                // 等待到绿灯
                t += change - (t % change);
            }
            t += time; // 赶路时间
            
            for(auto v: path[u]) {
                // 到达终点
                if(v == n) UpdateAns(t);
                
                // printf("u=%d v=%d t=%d step=%d secondAns=%d\n", u, v, t, step[v], GetSecondAns());
                if(Skip(v, t)) {
                    // printf("skip\n");
                    continue; // 剪枝：全是绿灯，依旧大于 secondAns
                }
                que.push(Node{t, v});
            }
        }
        
        
        
        return GetSecondAns();
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
