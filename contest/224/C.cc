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
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int ans = 0;

        int n = matrix.size();
        int m = matrix[0].size();

        vector<pair<int, int>> dp(m);
        for(int i=0;i<m;i++){
            dp[i] = {i, 0};
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j]){
                    dp[j].second++;
                }else{
                    dp[j].second = 0;
                }
            }

            sort(dp.begin(), dp.end(), [](const pair<int, int>&a, const pair<int, int>&b){
                return a.second > b.second;
            });

            for(int j=0;j<m;j++){
                ans = max(ans, dp[j].second * (j+1));
            }
            sort(dp.begin(), dp.end(), [](pair<int, int>&a, pair<int, int>&b){
                return a.first < b.first;
            });
        }


        return ans;
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
