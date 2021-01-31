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
    int countBalls(int lowLimit, int highLimit) {
        unordered_map<int, int> m;
        
        int ans = 0;
        for(int i=lowLimit;i<=highLimit;i++){
            int sum = 0;
            int tmp = i;
            while(tmp){
                sum += tmp%10;
                tmp /= 10;
            }
            
            m[sum]++;
            ans = max(ans, m[sum]);
        }
        
        return ans;
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
