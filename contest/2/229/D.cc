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


int dp[2][2010][2010];
class Solution {
        //vector<vector<int>> dp(1010, vector<int>(1010, -1));
        int mid, n;
        string s;
    
        int dfs(int l, int r, int limit){
            if(l > r) return 0;
            if(limit && (l >= mid || r < mid)){
                return 0; // 还没有相等的，不能越界
            }
            
            if(dp[limit][l][r] != -1){
                return dp[limit][l][r];
            }
            
            int ans = 0;
            
            if(s[l] == s[r]){
                ans = 2 + dfs(l+1, r-1, 0);  // 相等了，没有任何限制了
                if(l == r){
                    ans--;
                }
            }else{
                ans = max(dfs(l, r - 1, limit), dfs(l + 1, r, limit));
            }
            
            return dp[limit][l][r] = ans;
        }
    
public:
    int longestPalindrome(string& s1, string& s2) {
        s = s1 + s2;
        mid = s1.size();
        n = s.size();
        memset(dp, -1, sizeof(dp));
        return dfs(0, n-1, 1);
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
