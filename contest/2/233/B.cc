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
// reserve
// sum = accumulate(a.begin(), a.end(), 0);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;



class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        
        min_queue<pll> sell_que;
        max_queue<pll> buy_que;
        
        for(auto& v : orders){
            ll price = v[0], amount = v[1], orderType = v[2];

            if(orderType == 0){ // buy
            //如果该订单是一笔采购订单 buy ，则可以查看积压订单中价格 最低 的销售订单 sell 。如果该销售订单 sell 的价格 低于或等于 当前采购订单 buy 的价格，则匹配并执行这两笔订单，并将销售订单 sell 从积压订单中删除。否则，采购订单 buy 将会添加到积压订单中。
                
                while(amount > 0 && !sell_que.empty() && sell_que.top().first <= price){
                    auto p = sell_que.top(); sell_que.pop();
                    if(p.second > amount){
                        p.second -= amount;
                        amount = 0;
                        sell_que.push(p);
                    }else if(p.second <= amount){
                        amount -= p.second;
                    }
                }
                
                if(amount > 0){
                    buy_que.push({price, amount});
                }
            }else if(orderType == 1){ // sell
                //反之亦然，如果该订单是一笔销售订单 sell ，则可以查看积压订单中价格 最高 的采购订单 buy 。如果该采购订单 buy 的价格 高于或等于 当前销售订单 sell 的价格，则匹配并执行这两笔订单，并将采购订单 buy 从积压订单中删除。否则，销售订单 sell 将会添加到积压订单中。
                
                while(amount > 0 && !buy_que.empty() && buy_que.top().first >= price){
                    auto p = buy_que.top(); buy_que.pop();
                    if(p.second > amount){
                        p.second -= amount;
                        amount = 0;
                        buy_que.push(p);
                    }else if(p.second <= amount){
                        amount -= p.second;
                    }
                }
                
                if(amount > 0){
                    sell_que.push({price, amount});
                }
            }
        }
        
        
        ll ans = 0;
        
        while(!sell_que.empty()){
            ans = (ans + sell_que.top().second) % 1000000007;
            sell_que.pop();
        } 
        while(!buy_que.empty()){
            ans = (ans + buy_que.top().second) % 1000000007;
            buy_que.pop();
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
