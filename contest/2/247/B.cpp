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
    vector<int> tmp;
    int n, m;
    
    void Get(vector<vector<int>>& grid, int k){
        int up = k, down = n -  k - 1, left = k,  right = m - k - 1;
        // printf("k=%d up=%d down=%d left=%d right=%d\n", k, up, down, left, right);
        for(int i = left; i < right; i++) {
            tmp.push_back(grid[up][i]);
        }
        for(int i = up; i < down; i++) {
            tmp.push_back(grid[i][right]);
        }
        for(int i = right; i > left; i--) {
            tmp.push_back(grid[down][i]);
        }
        for(int i = down; i > up; i--) {
            tmp.push_back(grid[i][left]);
        }
    }
    void Set(vector<vector<int>>& grid, int k, int offset){
        int up = k, down = n - k - 1, left = k,  right = m - k - 1;
        int len = tmp.size() / 2; 
        // printf("k=%d len=%d\n", k, len);
        offset = offset % len;
        
        
        for(int i = left; i < right; i++) {
            grid[up][i] = tmp[offset++];
        }
        for(int i = up; i < down; i++) {
            grid[i][right] = tmp[offset++];
        }
        for(int i = right; i > left; i--) {
            grid[down][i] = tmp[offset++];
        }
        for(int i = down; i > up; i--) {
            grid[i][left] = tmp[offset++];
        }
        
    }
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        n = grid.size();
        m = grid[0].size();
        // printf("n=%d m=%d\n", n, m);
        
        tmp.reserve(n * 4 + m * 4);
        
        for(int i = 0; i * 2 < min(n, m); i++){
            tmp.clear();
            Get(grid, i);
            Get(grid, i);
            // printf("%d: ", i);
            // for(auto v: tmp) {
            //     printf("%d ", v);
            // }
            // printf("\n");
            Set(grid, i, k);
        }
        return grid;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
