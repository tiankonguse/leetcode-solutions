#include "base.h"

#define myprintf(format, args...) printf("line[%d]" format, __LINE__, ##args)
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


#define myprintf(format, args...) printf("line[%d]" format, __LINE__, ##args)
#define myprintf(format, args...)

const int N = 1111;
int pre[N],Rank[N];

void init(int n) {
    for(int i=0; i<n; i++) {
        pre[i] = i, Rank[i] = 0;
    }
}

int find_pre(int node) {
  if (pre[node] != node) {
    pre[node] = find_pre(pre[node]);
  }
  return pre[node];
}

void merge_pre(int from, int to) {
  from = find_pre(from);
  to = find_pre(to);
  if (from != to) {
    if (Rank[from] > Rank[to]) {
      pre[to] = from;
    } else {
      pre[from] = to;
      if (Rank[from] == Rank[to]) {
        ++Rank[to];
      }
    }
  }
}

class Solution {
    vector<vector<int>> restrictions;
    
    bool Check(int u, int v){
        int preu = find_pre(u), prev = find_pre(v);
        if(preu == prev) {
            return true; // 本来就是朋友，说明合法
        }
        myprintf("u=%d preu=%d v=%d prev=%d\n", u, preu, v, prev);
        
        for(auto&p: restrictions) {
            int pre1 = find_pre(p[0]);
            int pre2 = find_pre(p[1]);
            myprintf("p0=%d prep0=%d p1=%d prep1=%d\n", p[0], pre1, p[1], pre2);
            
            if(pre1 == preu && pre2 == prev) return false;
            if(pre1 == prev && pre2 == preu) return false;
        }
        
        merge_pre(u, v);
        return true;
        
    }
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions_, vector<vector<int>>& requests) {
        restrictions.swap(restrictions_);
        
        init(n);
        
        vector<bool> ans;
        ans.reserve(requests.size());
        for(auto&p: requests) {
            int u = p[0], v = p[1];
            ans.push_back(Check(u, v));
            myprintf("ans=%d\n", int(ans.back()));
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
