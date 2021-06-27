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
    vector<int> dp;  // -2 未计算。 -1 不可达， 其他：最小步数

    vector<set<int>> pre;
    vector<int> next;
    int n;
    int N;

    void Init(vector<vector<int>>& board){
        n = board.size();
        N = n * n;
        dp.resize(N+1, -1); 
        next.resize(N+1, -1);
        pre.resize(N+1);

        int index = 1;
        int flag = 1;
        for(int i = n-1; i >= 0; i--) {
            if(flag) {
                for(int j = 0; j < n; j++) {
                    next[index++] = board[i][j];
                }
            } else {
                for(int j = n - 1; j >= 0; j--) {
                    next[index++] = board[i][j];
                }
            }
            flag = 1 - flag;
        }

        for(int x = 1; x <= N; x++) { // 建图
            for(int j = 1; j <= 6; j++) {
                int next_v = x + j;
                if(next_v > N) continue;

                if(next[next_v] == -1) {
                    pre[next_v].insert(x);
                } else {
                    next_v = next[next_v];
                    pre[next_v].insert(x);
                }
            }
        }

    }
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        Init(board);

        queue<int> que;
        dp[N] = 0;
        que.push(N);


        while(!que.empty()) {
            int now = que.front(); que.pop();
            for(auto v: pre[now]) {
                if(dp[v] != -1) continue; // 已经有答案了
                dp[v] = dp[now] + 1;
                que.push(v);
            }
        }
        return dp[1];
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
