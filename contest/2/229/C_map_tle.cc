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
    map<pair<int, int>, int> cache;
    vector<int> nums;
    vector<int> multipliers;
    int n,m;
    
    int dfs(int l, int r){
        int i = (l-1) + (n-r) + 1;
        if(i > m){
            return 0;
        }
        
        pair<int, int> p = {l, r};
        if(cache.count(p)){
            return cache[p];
        }
        
        int leftVal = dfs(l+1, r) + multipliers[i-1] * nums[l-1];
        int rightVal = dfs(l, r-1) + multipliers[i-1] * nums[r-1];
        return cache[p] = max(leftVal, rightVal);
    }
    
public:
    int maximumScore(vector<int>& nums_, vector<int>& multipliers_) {
        nums.swap(nums_);
        multipliers.swap(multipliers_);
        n = nums.size();
        m = multipliers.size();
        return dfs(1, n);
    }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
