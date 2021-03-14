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
// const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;


class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        int minVal = nums[k];
        int len  = 1;
        int ans = minVal * len;
        int l = k - 1;
        int r = k + 1;
        
        while(l >= 0 || r < n){
            len++;
            
            int i = 0;
            if(l < 0){
                i = r;
                r++;
            }else if(r == n){
                i = l;
                l--;
            }else if(nums[l] < nums[r]){
                i = r;
                r++;
            }else{
                i = l;
                l--;
            }
            
            
            minVal = min(minVal, nums[i]);
            
            int tmpAns = minVal * len;
            if(tmpAns > ans){
                ans = tmpAns;
            }
        }
        return ans;
    }
};

int main() {
//   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
//   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
//   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
