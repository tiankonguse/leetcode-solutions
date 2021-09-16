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

const int maxn = 100005;
const int maxn_log = 20;
vector<int> g[maxn];
int f[maxn][maxn_log], dep[maxn];
int rankNum[maxn];

class Solution {
    int n;
    vector<int> parents;
    
    void Init(vector<int>& parents_, vector<int>& nums){
        parents.swap(parents_);
        n = parents.size();
        memset(rankNum, -1, sizeof(rankNum)); // -1 代表不存在

        for(int i = 0; i < n; i++) {
            dep[i] = 0;
            g[i].clear();
            memset(f[i], 0, sizeof(int) * maxn_log);

            rankNum[nums[i]] = i;
        }

        for(int i = 1; i < n; i++) { // 0 是根，所以从 1 开始
            g[parents[i]].push_back(i);
        }
    }

    void DfsRMQ(int u){
        for(int v: g[u]) {
            // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1。
            dep[v] = dep[u] + 1;
            f[v][0] = u; 

            // 初始化：其他的祖先节点：第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第 2^(i-1) 的祖先节点。
            for(int i = 1; i < maxn_log; i++) {
                f[v][i] = f[f[v][i-1]][i-1];
            }
            DfsRMQ(v);
        }
    }

    int Lca(int u, int v){
        if(dep[u] < dep[v]) swap(u, v);
        for(int d = dep[u] - dep[v], i = maxn_log - 1; d && i >= 0; i--) {
            if(d & (1<<i)) {
                u = f[u][i];
                d = d ^ (1<<i);
            }
        }

        if(u == v) return u;

        for(int i = maxn_log - 1; i >= 0; i--) {
            if(f[u][i] != f[v][i]) {
                u = f[u][i];
                v = f[v][i];
            }
        }
        return f[u][0];
    }

    vector<int> ans;
    int Fill(int p, int nxt){
        int pre = p;
        while(p != nxt) {
            p = parents[p];
            ans[p] = ans[pre];
        }
        return p;
    }

public:
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        Init(parents, nums);
        DfsRMQ(0);

        ans.resize(n, 1);
        int p = rankNum[1];
        if(p == -1) return ans;
        ans[p] = 2;
        
        for(int i = 2; i <= n; i++) {
            if(rankNum[i] == -1) {
                Fill(p, 0);
                break;
            }

            int nxt = Lca(p, rankNum[i]);
            p = Fill(p, nxt);
            ans[nxt] = i + 1;
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
