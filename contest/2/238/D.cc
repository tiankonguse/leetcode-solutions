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
// vector/array: upper_bound(vec.begin(), vec.end(), v)
// map: m.upper_bound(v)
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);
// unordered_map / unordered_set
// 排序，小于是升序：[](auto&a, auto&b){ return a < b; })
// 优先队列 priority_queue<Node>：大于是升序 
// struct Node{
//     int t;
//     bool operator<(const Node & that)const { return this->t > that.t; }
// };

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

typedef long long ll;

class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        
        if(restrictions.size() == 0){
            restrictions.push_back({n, n-1});
        }
        
        sort(restrictions.begin(), restrictions.end(), [](auto&a, auto&b){
            return a[0] < b[0];
        });
        
        
        if(restrictions[restrictions.size()-1][0] != n){
            restrictions.push_back({n, n-1});
        }
        
       
        
        stack<pair<ll, ll>> sta; //{id, heigh}
        sta.push({1, 0});
        
        for( auto& v: restrictions){
            ll id = v[0], maxHeight = v[1];
           // printf("id=%lld, maxHeight=%lld\n", id, maxHeight);
            
            // 此时，栈中至少有一个元素
            while(!sta.empty()){
                auto p = sta.top();
                
                ll dis = id - p.first;
                ll up = p.second + dis;
                ll down = p.second - dis;
                //printf("now = [%lld, %lld] up=%lld down=%lld\n", p.first, p.second, up, down);
                

                //致力于向上走，可以到达最大值 up
                if(up <= maxHeight){
                    sta.push({id, up});
                    break;
                }

                // 恰好可以向下走，到达最底部
                if(down == maxHeight){
                    sta.push({id, down});
                    break;
                }

                // 位于中间，还是可以到达的
                if(down < maxHeight){
                    //致力于向下走，可以到达，说明可以先向上，再向下
                    ll len = (id + maxHeight - p.first - p.second)/2;
                    ll newid = p.first + len;
                    ll newHeight = p.second + len;


                    // 第一种情况，先上再下
                    if(id - newid == newHeight - maxHeight){
                        sta.push({newid, newHeight});
                        sta.push({id, maxHeight});
                        break;
                    }

                    // 第二种情况：一平
                    if(p.first + 1 == id){
                        sta.push({id, maxHeight});
                        break;
                    }

                    // 第三种情况，先上，一平
                    if(newid + 1 == id){
                        sta.push({newid, newHeight});
                        sta.push({id, maxHeight});
                        break;
                    }

                    // 第四种情况，先上，一平，再下

                    sta.push({newid, newHeight});
                    sta.push({newid+1, newHeight});
                    sta.push({id, maxHeight});
                    break;
                }

                // 此时无法到达，需要进行调整
                sta.pop(); 
            }
            
        }
        
        ll ans  = 0;
        while(!sta.empty()){
            auto p = sta.top(); sta.pop();
            if(p.first <= n){
                ans = max(ans, p.second);
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
