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

/*
int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

int dir[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};

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


sum = accumulate(a.begin(), a.end(), 0);
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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

struct Node{
    string str;
    int one;
    void Init(int n, int val){
        str.resize(n, '0' + val);
        if(val) {
            one = n;
        } else {
            one = 0;
        }
    }
    void fix(int idx){
        if(str[idx] == '0') {
            str[idx] = '1';
            one++;
        }
    }
    void unfix(int idx){
        if(str[idx] == '1') {
            str[idx] = '0';
            one--;
        }
    }
};

class Bitset {
    Node buf[2];
    int index;
    
public:
    Bitset(int n) {
        buf[0].Init(n, 0);
        buf[1].Init(n, 1);
        index = 0;
        // printf("init str=%s one=%d\n", buf[index].str.c_str(), buf[index].one);
        // printf("1-index init str=%s one=%d\n", buf[1-index].str.c_str(), buf[1-index].one);
    }
    
    void fix(int idx) {
        buf[index].fix(idx);
        buf[1-index].unfix(idx);
        // printf("fix(%d) str=%s one=%d\n", idx, buf[index].str.c_str(), buf[index].one);
        // printf("1-indx fix(%d) str=%s one=%d\n", idx, buf[1-index].str.c_str(), buf[1-index].one);
    }
    
    void unfix(int idx) {
        buf[index].unfix(idx);
        buf[1-index].fix(idx);
        // printf("unfix(%d) str=%s one=%d\n", idx,  buf[index].str.c_str(), buf[index].one);
        // printf("1-index unfix(%d) str=%s one=%d\n", idx,  buf[1-index].str.c_str(), buf[1-index].one);
    }
    
    void flip() {
        index = 1 - index;
        // printf("flip str=%s one=%d\n", buf[index].str.c_str(), buf[index].one);
        // printf("1-index flip str=%s one=%d\n", buf[1-index].str.c_str(), buf[1-index].one);
    }
    
    bool all() {
        // printf("all str=%s one=%d ret=%d\n", buf[index].str.c_str(), buf[index].one, buf[index].one == buf[index].str.size());
        return buf[index].one == buf[index].str.size();
    }
    
    bool one() {
        // printf("one str=%s one=%d ret=%d\n", buf[index].str.c_str(), buf[index].one, buf[index].one > 0);
        return buf[index].one > 0;
    }
    
    int count() {
        // printf("count str=%s one=%d ret=%d\n", buf[index].str.c_str(), buf[index].one, buf[index].one);
        return buf[index].one;
    }
    
    string toString() {
        // printf("toString str=%s one=%d\n", buf[index].str.c_str(), buf[index].one);
        return buf[index].str;
    }
};

/**
 * Your Bitset object will be instantiated and called as such:
 * Bitset* obj = new Bitset(size);
 * obj->fix(idx);
 * obj->unfix(idx);
 * obj->flip();
 * bool param_4 = obj->all();
 * bool param_5 = obj->one();
 * int param_6 = obj->count();
 * string param_7 = obj->toString();
 */

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  priority_queue<Node> que;
  que.push(Node(1));
  que.push(Node(2));
  while (!que.empty()) {
    printf("val:%d\n", que.top().t);
    que.pop();
  }

  return 0;
}