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
class Solution {
public:
    string maximumTime(string time) {
        // 00:?? ~ 09:??
        // 10:?? ~ 19:??
        // 20:?? ~ 23:??
        
        if(time[0] == '?'){
            if(time[1] == '?'){
                time[0] = '2';
            }else if(time[1] <= '3'){
                time[0] = '2';
            }else{
                time[0] = '1';
            }
        }
        
        if(time[1] == '?'){
            if(time[0] == '2'){
                time[1] = '3';
            }else{
                time[1] = '9';
            }
        }
        
        // 2=> ：
        
        if(time[3] == '?'){
            time[3]  = '5';
        }
        
        if(time[4] == '?'){
            time[4]  = '9';
        }
        return time;
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
