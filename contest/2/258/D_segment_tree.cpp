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


const int N = 100000;
const int M = 20 * N;
class Solution {
    vector<vector<int>> g;
    vector<int> root;
    vector<int> ans;
    int L[M], R[M], V[M]; 

    int index;
    void Insert(int& x, int l, int r, int v) {
        x = ++index;
        L[x] = R[x] = 0;
        V[x] = 1;
        if(l == r) return ;
        int mid = (l + r) >> 1;
        if(v <= mid) {
            Insert(L[x], l, mid, v);
        } else {
            Insert(R[x], mid + 1, r, v);
        }
    }

    int Merge(int x, int y) {
        if(x == 0 || y == 0) return x == 0 ? y : x;
        V[x] += V[y];
        L[x] = Merge(L[x], L[y]);
        R[x] = Merge(R[x], R[y]);
        return x;
    }

    int Query(int x, int l, int r){
        if(x == 0) return l;
        if(V[x] == r - l + 1) return r + 1; 

        int mid = (l + r) >> 1;
        int leftAns = Query(L[x], l, mid);
        if(leftAns <= mid) return leftAns;

        return Query(R[x], mid + 1, r);
    }

    void Solver(int x) {
        for(auto v: g[x]) {
            Solver(v);
            root[x] = Merge(root[x], root[v]);
        }
        ans[x] = Query(root[x], 1, N);
    }

public:
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        int n = parents.size();
        g.resize(n);
        for(int i = 1; i < n; i++) {
            g[parents[i]].push_back(i);
        }

        index = 0;
        root.resize(n, 0);
        for(int i = 0; i < n; i++) {
            Insert(root[i], 1, N, nums[i]);
        }

        ans.resize(n, 1);
        Solver(0);
        return ans;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
