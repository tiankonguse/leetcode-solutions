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


typedef int ll;
typedef int LL;

// 1.bulid(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 11111;

int maxNM;

struct SegTree {
  LL sign[maxn << 2];  //
  LL maxMal[maxn << 2];

  LL str[maxn];

  void PushUp(int rt) {
    maxMal[rt] = max(maxMal[rt << 1], maxMal[rt << 1 | 1]);
  }
  void PushDown(int rt) {
    if (sign[rt]) {
      sign[rt << 1] = max(sign[rt], sign[rt << 1]);
      sign[rt << 1 | 1] = max(sign[rt << 1 | 1], sign[rt]);

      maxMal[rt << 1] = max(maxMal[rt << 1], sign[rt]);
      maxMal[rt << 1 | 1] = max(maxMal[rt << 1 | 1], sign[rt]);
      sign[rt] = 0;
    }
  }
  void bulid(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    if (l == r) {
      maxMal[rt] = str[l];
      return;
    }
    int m = (l + r) >> 1;
    bulid(lson);
    bulid(rson);
    PushUp(rt);
  }
  void update(int L, int R, int add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      sign[rt] = max(sign[rt], add);
      maxMal[rt] = max(maxMal[rt], add);
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, add, lson);
    if (R > m) update(L, R, add, rson);
    PushUp(rt);
  }
  LL queryMax(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return maxMal[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    LL ret = -1;
    if (L <= m) {
      ret = max(ret, queryMax(L, R, lson));
    }
    if (m < R) {
      ret = max(ret, queryMax(L, R, rson));
    }
    return ret;
  }
};

SegTree lineSegTree;


class Solution {

public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        map<LL, int> m;
        for(auto& v: buildings) {
            ll l = v[0], r = v[1];
            m[l];
            m[r-1];
            m[r];
        }

        int index = 1;
        for(auto& p: m) {
            p.second = index++;
        }
        maxNM = index;



        vector<LL> indexs(maxNM+1, 0);
        for(auto& p: m) {
            indexs[p.second] = p.first;
        }

        memset(lineSegTree.str, 0, sizeof(lineSegTree.str));
        lineSegTree.bulid();

        for(auto& v: buildings) {
            lineSegTree.update(m[v[0]], m[v[1]-1], v[2]);
        }

        vector<vector<int>> ans;

        ll pre_h = 0;
        for(int i = 1; i < index; i++){
            ll h = lineSegTree.queryMax(i, i);
            if(h != pre_h){
                ans.push_back({indexs[i], h});
                pre_h = h;
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
