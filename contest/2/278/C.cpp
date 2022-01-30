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

typedef long long ll;
class Solution {
    ll exgcd(ll a,ll b,ll &x,ll &y){
        if(b==0){x=1,y=0;return a;}
        ll d=exgcd(b,a%b,x,y);
        ll t=x;x=y;y=t-a/b*y;
        return d;
    }
    
    // 求(a/b)% c(乘法逆元)
    ll div_mod(ll a,ll b,ll c){
        if(a % b == 0) {
          return a/b % c;
        } else {
          ll x, y;
          exgcd(b,c,x,y);
          return ((a%c)*(x%c))%c;

        }
    }
    
public:
    // 需要除法逆元，先暴力做
    string subStrHashForce(string& s, int p, int m, int k, ll h) {
        int n = s.length();
        int pos = 0;
        for(int i = 0; i + k <= n; i++) {
            ll pre = 1, sum = 0;
            for(int j = 0; j < k; j++) {
                ll v = s[i+j] - 'a' + 1;
                sum = (sum + v * pre) % m;
                pre = (pre * p) % m; 
            }
            printf("i=%d sub=%s sum=%lld\n", i, s.substr(i, k).c_str(), sum);
            if(sum == h) {
                pos = i;
            }
        }
        return s.substr(pos, k);
    }
    string subStrHash(string& s, int p, int m, int k, int h) {
        int n = s.length();
        //subStrHashForce(s,p,m,k,h);
        ll pre = 1;
        ll sum = 0;
        for(int i = n-1, j = 1; j < k; i--, j++) {
            ll v = s[i] - 'a' + 1;
            sum = (sum * p + v)  % m;
            pre = (pre * p) % m; 
        }
        
        int pos = 0;
        for(int i = n - 1; i >= k - 1; i--) {
            ll firstVal = s[i-k+1] - 'a' + 1;
            sum = (sum * p + firstVal) % m;
            
            //printf("i=%d sub=%s sum=%lld h=%lld\n", i-k+1, s.substr(i-k+1, k).c_str(), sum, h);
            if(sum == h) {
                pos = i-k+1;
            }
            
            ll lastVal = s[i] - 'a' + 1;
            sum = (sum - (lastVal * pre)% m + m) % m;
        }
        return s.substr(pos, k);
    }  
    string subStrHashEx(string& s, int p, int m, int k, int h) {
        int n = s.length();
        
        vector<ll> nums(n, 0);
        
        ll pre = 1;
        for(int i = 0; i < n; i++) {
            ll v = s[i] - 'a' + 1;
            nums[i] = v * pre % m;
            pre = (pre * p) % m; 
        }
        
        ll sum = 0;
        for(int i = 0; i < k - 1; i++) {
            sum = (sum + nums[i]) % m;
        }
        
        
        for(int i = 0; i + k < n; i++) {
            sum = (sum + nums[i+k-1]) % m;
            
            printf("i=%d sub=%s sum=%lld h=%lld\n", i, s.substr(i, k).c_str(), sum, h);
            if(sum == h) {
                return s.substr(i, k);
            }
            
            sum = (sum + m - nums[i]) % m;
            h = (h * p) % m;
        }
        return s;
    }
    string subStrHashGcd(string& s, int p, int m, int k, int h) {
        subStrHashForce(s,p,m,k,h);
        int n = s.length();
        printf("n=%d m=%d k=%d\n", n, m, k);
        ll pre = 1, sum = 0;
        ll lastPre = 1;
        for(int j = 0; j < k; j++) {
            ll v = s[j] - 'a' + 1;
            sum = (sum + v * pre) % m;
            lastPre = pre;
            pre = (pre * p) % m; 
        }
        
        printf("i=%d, sub=%s sum=%lld\n", 0, s.substr(0, k).c_str(), sum);
        if(sum == h) {
            return s.substr(0, k);
        }
        
        
        
        for(int i = 0; i + k < n; i++) {
            // sum = (sum - a)/p + v * lastPre
            
            ll a = s[i] - 'a' + 1;
            ll v = s[i+k] - 'a' + 1;
            
            sum = (sum + m - a) % m;
            sum = div_mod(sum, p, m);
            sum = (sum + v * lastPre) % m;
            printf("i=%d, sub=%s sum=%lld\n", i+1, s.substr(i+1, k).c_str(), sum);
            if(sum == h) {
                return s.substr(i+1, k);
            }
        }
        return s;
    }
};

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
