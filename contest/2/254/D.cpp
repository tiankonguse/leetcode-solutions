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


int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

class Solution {
    int row;
    int col;
    vector<vector<int>> cells;
    
    vector<vector<int>> g;
    vector<vector<int>> cache;
    
    void Init(int mid){
        for(int i=0;i<row;i++) {
            for(int j=0;j<col;j++) {
                g[i][j] = 0;
                cache[i][j] = 0;
            }
        }
        
        for(int i=0;i<mid;i++) {
            int x = cells[i][0], y = cells[i][1];
            g[x-1][y-1] = 1;
        }
    }
    
    bool Dfs(int x, int y){
        // printf("x=%d y=%d\n", x, y);
        if(x < 0 || x >= row || y < 0 || y >= col) return false;
        if(g[x][y] == 1) return false; // 此路不通
        if(x == row - 1) return true; // 到达目的地
        
        if(cache[x][y]) return false; // 之前走过，此路不通
        cache[x][y] = true;
        
        for(int i=0;i<4;i++) {
            int X = dir[i][0] + x;
            int Y = dir[i][1] + y;
            
            if(Dfs(X, Y)) return true;
        }
        return false;
    }
    
    bool Check(int mid){
        Init(mid);
        // printf("init end\n");
        for(int i=0;i<col;i++) {
            if(Dfs(0, i)){
                return true;
            }
        }
        return false;
    }
public:
    int latestDayToCross(int row_, int col_, vector<vector<int>>& cells_) {
        row = row_;
        col = col_;
        cells.swap(cells_);
        
        if(col == 1) return 0; // 只有一列
        if(row == 1) return col - 1; // 只有一行
        
        g.resize(row, vector<int>(col, 0));
        cache.resize(row, vector<int>(col, 0));
        
        int l = 0, r = cells.size();
        while(l < r) {
            int mid = (l + r)/ 2;
            if(Check(mid)) {
                l = mid + 1;
            }else {
                r = mid;
            }
        }
        return l - 1;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
