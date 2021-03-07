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
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();
        const int kMaxCol = 1<<10;
        const int kMaxVal = n;
        vector<map<int, int>> grid(k);
        
        for(int i = 0; i < n; i++){
            grid[i % k][nums[i]]++;
        }
        // for(int i=0;i<k;i++){
        //     grid[i][0];
        // }
        
        vector<int> dp(kMaxCol, kMaxVal);
        vector<int> tmpDp(kMaxCol, n);
        int minNum = n;
        int oneAns = 0;
        
        dp[0] = 0;
        for(auto& col: grid){
            int sumNum = 0, maxNum = 0;
            for(auto&p : col){
                sumNum += p.second;
                maxNum = max(maxNum, p.second);
            }
            minNum = min(minNum, maxNum);
            oneAns += sumNum - maxNum;
            
            
            tmpDp.clear();
            tmpDp.resize(kMaxCol, kMaxVal);
            for(auto&p : col){
                int i = p.first;
                int num = p.second;
                int v = sumNum - num;
                for(int j = 0; j < kMaxCol; j++){
                    tmpDp[i^j] = min(tmpDp[i^j], dp[j] + v);
                }
            }
            tmpDp.swap(dp);
        }
        return min(dp[0], oneAns+minNum);
        
        
    }
};
int main() {
  // vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  // vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  // TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
