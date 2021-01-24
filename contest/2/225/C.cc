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
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        vector<int> ans;
        ans.reserve(n*m);
        
        dp[0][0] = matrix[0][0];
        for(int i=1;i<n;i++){
            dp[i][0] = matrix[i][0] ^ dp[i-1][0];
        }
        for(int j=1;j<m;j++){
            dp[0][j] =  matrix[0][j] ^ dp[0][j-1];
        }
        
        
        for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                dp[i][j] = matrix[i][j] ^ dp[i-1][j] ^ dp[i][j-1] ^ dp[i-1][j-1];
            }
        }
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                ans.push_back(dp[i][j]);
            }
        }
        
        sort(ans.begin(), ans.end(), [](int a, int b){return a>b;});
        return ans[k-1];
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
