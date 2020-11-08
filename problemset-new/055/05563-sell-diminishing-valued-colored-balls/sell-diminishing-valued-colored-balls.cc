#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T> >;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;


class Solution {
    map<ll, int> m;
    ll ans;
    
    ll getNext(){
        auto it = m.end(); it--;
        return it->first;
    }
    
    // orders=252264991 v=773160767 n = 1 size = 0
    void LastScore(ll v, int n, int& orders){
        int fullNum = orders / n;
        int leftNum = orders % n;

        // fullNum * n: v + v-1 + v-2 + ... v-fullNum+1
        ll allScore = (v + v-fullNum+1) * fullNum / 2 % mod;
        allScore = (allScore * n) % mod;
        ans = (ans + allScore) % mod;

        // leftNum * 1：v-fullNum
        ll leftScore =  (v-fullNum) * leftNum % mod;
        ans = (ans + leftScore) % mod;
        orders = 0;
    }
    
public:
    int maxProfit(vector<int>& inventory, int orders) {
        ans = 0;
        m[0] = 0;
        for(auto v: inventory) m[v]++;
        
        while(orders > 0){
            auto it = m.end(); it--;
            ll v = it->first;
            int n = it->second;
            m.erase(it);
            
            ll nextv = getNext();
            ll fullNum = v - nextv;

            // fullNum: v, v-1, ..., v-fullNum+1
            ll allScore = (v + v-fullNum+1) * fullNum / 2 % mod; 
            allScore = (allScore * n) % mod;

            if(fullNum * n <= orders){ // 全选还有剩余
                ans = (ans + allScore) % mod;
                orders -= fullNum * n;
                m[nextv] += n;
            }else{
                LastScore(v, n, orders); //没剩余，最后一次机会了
            }
        }
        
        return ans;
    }
};

int main() {
    TEST_SMP2(Solution, maxProfit, 14, vector<int>({2,5}), 4);
    TEST_SMP2(Solution, maxProfit, 19, vector<int>({3,5}), 6);
    TEST_SMP2(Solution, maxProfit, 110, vector<int>({2,8,4,10,6}), 20);
    TEST_SMP2(Solution, maxProfit, 21, vector<int>({1000000000}), 1000000000);

    return 0;
}
