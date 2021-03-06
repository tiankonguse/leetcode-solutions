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



const int max3 = 2100, max4 = 11100, max5 = 100100, max6 = 2000100;
typedef long long ll;
const int mod = 1e9 + 7;
ll sum[max5];

class Solution {
public:
    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
        int n = packages.size();
        sort(packages.begin(), packages.end());
        
        sum[0] = 0;
        for(int i=1;i <=n;i++){
            sum[i] = sum[i-1] + packages[i-1];
        }
        
        ll ans = -1;
        for(auto& box: boxes){
            sort(box.begin(), box.end());
            
            // 剪枝
            if(packages.back() > box.back()){
                continue;
            }
            
            
            ll tmp_ans = 0;
            int left = 0;
            
            for(auto b: box){
                if(b < packages.front()){
                    continue;
                }
                
                
                auto it = upper_bound(packages.begin(), packages.end(), b);
                it--;
                
                int pos = it - packages.begin();
                if(pos < left) continue;
                
                // [left, pos] 可以放在 b 中
                ll num = pos - left + 1;
                tmp_ans += num * b - (sum[pos+1] - sum[left]);
                
                left = pos + 1;
            }
            
            if(ans == -1){
                ans = tmp_ans;
            }else{
                ans = min(ans, tmp_ans);
            }
            
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
