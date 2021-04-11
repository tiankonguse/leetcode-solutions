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

// lower_bound 大于等于
// upper_bound 大于
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);
// unordered_map / unordered_set

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

typedef long long ll;

class Que{
    public:
    Que(char* str = ""){
        name = str;
    }
    std::string name;
    map<ll, int> que;
    ll sum = 0;
    ll num = 0;

    ll GetMinVal(){
        return que.begin()->first;
    }

    ll GetMaxVal(){
        return que.rbegin()->first;
    }

    void add(ll v){
        num++;
        sum += v;
        que[v]++;
    }
    void del(ll v){
        auto it = que.find(v);
        if(it == que.end()){
            return;
        }

        sum -= v;
        num--;

        it->second--;
        if(it->second == 0){
            que.erase(it);
        }
    }
};
class MKAverage {
    int M,K;
    queue<ll> base_que;
    
    Que small_que, mid_que, big_que;
    
    
    void add(ll v){
        if(big_que.num < K){ //优先填充大队列
            big_que.add(v);
            return;
        }
        
        // 判断是否可以插入到大队列
        ll big_min_val = big_que.GetMinVal();
        if(big_min_val < v){ //需要插入到 big 队列
            big_que.add(v);
            big_que.del(big_min_val);
            v = big_min_val;
        }
        
        // 优先填充到小队列 
        if(small_que.num < K){
            small_que.add(v);
            return;
        }
        
        //判断是否可以插入到小队列
        ll small_max_val = small_que.GetMaxVal();
        if(small_max_val > v){
            small_que.add(v);
            small_que.del(small_max_val);
            v = small_max_val;
        }
        
        mid_que.add(v);
    }
    

    void del(ll v){
        // 优先从中间删除
        if(mid_que.que.count(v)){
            mid_que.del(v);
            return ;
        }
        
        //中间没找到，两边二选一
        
        
        //判断大队列
        if(v >= big_que.GetMinVal()){
            big_que.del(v);
            
            // 此时需要从中间补回来一个最大值
            v = mid_que.GetMaxVal();
            mid_que.del(v);
            big_que.add(v);
            return;
        }
        
        //此时肯定是小队列
        if(v <= small_que.GetMaxVal()){
            small_que.del(v);
            
            // 此时需要从中间补回来一个最大值
            v = mid_que.GetMinVal();
            mid_que.del(v);
            small_que.add(v);
            return;
        }
        
        
    }
    
public:
    MKAverage(int m, int k) {
        M = m, K = k;
    }
    
    void addElement(int num) {
        base_que.push(num);
        add(num);
        
        if(base_que.size() > M){
            num = base_que.front();
            base_que.pop();
            del(num);
        }
    }
    
    int calculateMKAverage() {
        if(base_que.size() < M){
            return -1;
        }else{
            ll sum = mid_que.sum, num = mid_que.sum;
            return ((sum * 1.0 + 0.5)  / mid_que.num); 
        }
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
