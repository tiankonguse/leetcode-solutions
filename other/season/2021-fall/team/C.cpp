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

struct Node{
    ll a, b;  // a * x + b
    Node(ll a=0, ll b=0):a(a), b(b){}
    
    void Init(ll a, ll b){
        this->a = a;
        this->b = b;
    }
    
    void Add(Node& o){
        a = a + o.a;
        b = b + o.b;
    }
    void Minute(Node& o){
        a = a - o.a;
        b = b - o.b;
    }
    
};

class Solution {
    int n;
    vector<vector<int>> tree;
    vector<Node> nodes;
public:
    vector<int> volunteerDeployment(vector<int>& finalCnt, long long totalNum, vector<vector<int>>& edges, vector<vector<int>>& plans) {
        n = finalCnt.size() + 1;
        tree.resize(n);
        for(auto&p : edges) {
            int x = p[0], y = p[1];
            tree[x].push_back(y);
            tree[y].push_back(x);
        }
        
        nodes.resize(n);
        nodes[0].Init(1, 0);
        for(int i=1;i<n;i++) {
            nodes[i].Init(0, finalCnt[i-1]);
        }
        
        int m = plans.size();
        for(int i = m - 1; i >= 0; i--) {
            int num = plans[i][0];
            int idx = plans[i][1];
            if(num == 1) {
                nodes[idx].Add(nodes[idx]);
            } else if(num == 2){
                for(auto v: tree[idx]) {
                    nodes[v].Minute(nodes[idx]);
                }
            }else {
                for(auto v: tree[idx]) {
                    nodes[v].Add(nodes[idx]);
                }
            }
        }
        
        Node sum(0, 0);
        for(auto& v: nodes) {
            sum.Add(v);
        }
        
        int x = (totalNum - sum.b) / sum.a;
        
        vector<int> ans(n);
        for(int i=0;i<n;i++) {
            ans[i] = nodes[i].a * x + nodes[i].b;
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
