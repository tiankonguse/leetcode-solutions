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

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;
typedef long long ll;
class Solution {
public:
    int countPairs(vector<int>& deliciousness) {
        ll one = 1;
        vector<ll> base(23, 0);
        base.clear();
        for(int i=0;i<=21;i++){
            base.push_back(one<<i);
            //printf("i=%d base=%lld\n", i, one<<i);
        }
        
        
        unordered_map<ll, ll> m;
        for(auto v: deliciousness){
            m[v]++;
        }
        
        ll ans = 0;
        for(auto a: deliciousness){
            for(auto sum: base){
                //printf("a=%lld sum=%lld b=%lld\n", a, sum, sum-a);
                if(a > sum){
                    continue;
                }
                
                ll b = sum - a;
                if(m.count(b) == 0){
                    continue;
                }
                
                ans += m[b];
                if(a == b){
                    ans--;
                }
            }
        }
        
        return ans/2 % 1000000007;
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
