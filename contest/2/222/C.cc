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
    vector<ll> sum;
    
    // [1, R]
    // flag: 1 最小值， 0 最大值
    ll Search(int R, ll val, int flag){
        //printf("L=%d R=%d val=%d flag=%d\n", L, R, val, flag);
        // 剪枝
        if((sum[R] - sum[0] + 1)/2 > val){
            //printf("skip\n");
            return -1; 
        }
        
        
        ll l = 2;
        ll r = R + 1;
        ll ans = -1;
        // [l, r)
        while(l < r){
            ll mid = (l+r)/2;
            // [1, mid) , [mid, R+1)
            ll left_val = sum[mid-1];
            ll right_val = sum[R] - left_val;

            
            // 左边大，右移
            if(left_val > right_val){
                r = mid;
                continue;
            }
            
            // 右部大，左移
            if(right_val > val){
                l = mid + 1;
                continue;
            }
            
            
            // 此时 left_val <= right_val <= val
            if(ans == -1){
                ans = mid;
            }
            if(flag){
                ans = min(ans, mid);
                r = mid; // 左移，寻找最小值
            }else{
                ans = max(ans, mid);
                l = mid + 1; // 右移，寻找最大值
            }
            
        }
        
        return ans;
    }
    
public:
    ll waysToSplit(const vector<int>& nums) {
        int n = nums.size();
        //printf("n=%d\n", n);
        ll ans = 0;
        sum.resize(n+1);
        sum.clear();
        
        ll tmp = 0;
        sum.push_back(tmp);
        for(auto v: nums){
            tmp += v;
            sum.push_back(tmp);
        }
        
        // 至少两个
        for(int i=3;i<=n;i++){
            ll right_val = sum[n] - sum[i-1]; //[i, n]
            //printf("i=%d right_val=%d\n", i, right_val);
            ll min_mid = Search(i-1, right_val, 1);
            //printf("min_mid=%d\n", min_mid);
            if(min_mid == -1){
                continue;
            }
            ll max_mid = Search(i-1, right_val, 0);
            //printf("max_mid=%d\n", max_mid);
            ans += max_mid - min_mid + 1;
        }
        
        
        return ans%1000000007;
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
