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

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;
typedef long long ll;
class Solution {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        int n = candiesCount.size();
        vector<ll> sum(n, 0);
        
        ll pre = 0;
        for(int i=0;i<n;i++){
            pre += candiesCount[i];
            sum[i] = pre;
        }
        
        vector<bool> ans;
        ans.reserve(queries.size());
        
        for(auto& p: queries){
            int type = p[0];
            ll day = p[1];
            ll cap = p[2];
            
            ll minDay = 0, maxDay = 0; // [minDay ,maxDay]
            maxDay = sum[type] - 1; 
            
            ll preNum = 0;
            if(type > 0){
                preNum = sum[type - 1];
            }
            
            if(preNum < cap){
                minDay = 0;
            }else{
                minDay = preNum/cap;
            }
            
            if(day >= minDay && day <= maxDay){
                ans.push_back(true);
            }else{
                ans.push_back(false);
            }
            
            
        }
        
        return ans;
        
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
