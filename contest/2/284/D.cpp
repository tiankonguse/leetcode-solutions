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
int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

int& myMax(int& a, int b) {
  if (a < 0) {
    a = b;
  } else if (a < b) {
    a = b;
  }
  return a;
}
int& myMin(int& a, int b) {
  if (a < 0) {
    a = b;
  } else if (a > b) {
    a = b;
  }
  return a;
}

/*

lower_bound 大于等于
upper_bound 大于

vector / array : upper_bound(vec.begin(), vec.end(), v)
map: m.upper_bound(v)

区间 [l,r]内满足的个数：
upper_bound(vec.begin(), vec.end(), r) - lower_bound(vec.begin(), vec.end(), l);
std::distance(v.begin(), it)
map/set distance 复杂度 O(N)
vector/数组 distance 复杂度 O(1)

vector预先分配内存 reserve
反转 reverse(v.begin(), v.end())


sum = accumulate(a.begin(), a.end(), 0ll);
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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 10000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

typedef long long ll;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;

template <class T>
using max_queue = priority_queue<T>;

class Solution {
    void Dfs(int n, int x, vector<ll>& dis, vector<vector<pair<int, ll>>>& g){ // x 到 Y0 的距离已经求出来了
        dis.resize(n, -1);
        
        min_queue<pair<ll, int>> que;
        que.push({0, x});
        dis[x] = 0;
        
        while(!que.empty()) {
            auto p = que.top();que.pop();
            ll c = p.first;
            int x = p.second;
            
            if(dis[x] < c){ // 有更优的路径
                continue; 
            }
            
            for(auto&e: g[x]){
                int y = e.first;
                ll cost = c + e.second;
                
                if(dis[y] == -1 || dis[y] > cost){
                    dis[y] = cost;
                    que.push({cost, y});
                }
            }
        }
    }
    
public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int Y1, int Y2, int Y0) {
        vector<vector<pair<int, ll>>> g[3];
        vector<ll> dis[3];
        
        g[0].resize(n), g[1].resize(n), g[2].resize(n);
        
        for(auto& e: edges){
            int x = e[0], y = e[1];
            ll v = e[2];
            g[0][y].push_back({x, v});
            g[1][x].push_back({y, v});
            g[2][x].push_back({y, v});
        }
        
        Dfs(n, Y0, dis[0], g[0]);
        Dfs(n, Y1, dis[1], g[1]);
        Dfs(n, Y2, dis[2], g[2]);
        
        if(dis[0][Y1] == -1 || dis[0][Y2] == -1){
            return -1;
        }
        
        
        ll ans = dis[0][Y1] + dis[0][Y2];
        for(int i = 0; i < n; i++){
            if(dis[0][i] == -1 || dis[1][i] == -1 || dis[2][i] == -1) {
                continue;
            }
            ll tmp = dis[0][i] + dis[1][i] + dis[2][i];
             if(ans > tmp){
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
