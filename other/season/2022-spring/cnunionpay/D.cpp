#include "base.h"

#define myprintfex(format, args...) printf("line[%d]" format, __LINE__, ##args)
// #define myprintfex(format, args...)

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
unordered_map / unordered_set

lower_bound 大于等于
upper_bound 大于
reserve 预先分配内存 

vector / array : upper_bound(vec.begin(), vec.end(), v)
map: m.upper_bound(v)

区间 [l,r]内满足的个数：
std::distance(v.begin(), it)
map/set distance 复杂度 O(N)
vector/数组 distance 复杂度 O(1)

upper_bound(vec.begin(), vec.end(), r) - lower_bound(vec.begin(), vec.end(), l);



反转 reverse(v.begin(), v.end())


sum = accumulate(a.begin(), a.end(), 0ll);

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


typedef __int128_t int128;
typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};


// const LL INF = 0x3f3f3f3f3f3f3f3fll;
const ll INF = (ll)1e18;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 20100, max5 = 200100, max6 = 2000100;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define FOR(i, a, b) for (auto i = a; i < b; ++i)
#define FOR1(i, a, b) for (auto i = a; i <= b; ++i)
#define DWN(i, b, a) for (auto i = b - 1; i >= a; --i)
#define DWN1(i, b, a) for (auto i = b; i >= a; --i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()



typedef long long ll;
const ll mod = 1000000007;
const ll base = 1005;

class Solution {
    map<ll, ll> m;
    ll n;
    void Init(vector<vector<int>>& nums){
        n = nums.size();
        
        for(auto&vv: nums){
            sort(vv.begin(), vv.end());
            ll pre = 0;
            for(auto v: vv){
                pre = pre * base + v;
            }
            m[pre]++;
        }
        
    }
public:
    int coopDevelop(vector<vector<int>>& nums) {
        Init(nums);
        
        ll ans = n * (n-1) / 2;
         
        for(auto&vv: nums){ // 子集去重
            int k = vv.size();
            for(int i = 1;i < (1<<k) - 1; i++){ 
                int cnt = 0;
                ll pre = 0;
                for(int j = 0; j < k; j++){
                    if((i>>j) & 1) {
                        pre = pre * base + vv[j];
                    }
                }
                if(m.count(pre) > 0) {
                    ans -= m[pre];
                }
            }
        }
        
        for(auto p: m) { // 相同去重
            ll k = p.second;
            ans -= k * (k - 1) / 2; 
        }
        
        
        return ans % mod;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
