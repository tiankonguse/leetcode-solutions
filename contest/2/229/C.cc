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
    int maximumScore(vector<int>& nums, vector<int>& muls) {
        int n = nums.size();
        int m = muls.size();
        vector<vector<int>> dp(m+1, vector<int>(m+1, 0)); // [left][index]
        
        int ans = 0;
        
        for(int index = m; index > 0; index--){
            for(int l = index; l > 0; l--){
                int r = l + n - index;
                
                if(index == m){ //只能取一个
                    dp[l][index] = max(nums[l-1] * muls[index-1], nums[r-1] * muls[index-1]);
                }else{
                    int leftVal = dp[l+1][index+1] + nums[l-1] * muls[index-1];
                    int rightVal = dp[l][index+1] + nums[r-1] * muls[index-1];
                    dp[l][index] = max(rightVal, leftVal);
                }
            }
        }
        
        return dp[1][1];
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
