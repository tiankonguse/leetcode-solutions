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
bool dp[2010][2010];
class Solution {
    int n;
    string s;
    
    void TryCenter(int l, int r){
        while(l >= 0 && r < n && s[l] == s[r]){
            dp[l][r] = true;
            l--, r++;
        }
    }
    
public:
    bool checkPartitioning(string& s_) {
        s.swap(s_);
        
        n = s.length();
        memset(dp, 0, sizeof(dp));
        
        for(int i=0;i<n;i++){
            TryCenter(i, i);  // i 为中心
            TryCenter(i-1, i); // i-1~i 为中心
        }
        
        for(int l=1;l<n;l++){
            for(int r=l;r<n-1;r++){
                // [0, l-1], [l, r], [r+1, n-1]
                
                if(dp[0][l-1] && dp[l][r] && dp[r+1][n-1]){
                    return true;
                }
            }
        }
        return false;
        
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
