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
// std::lower_bound (v.begin(), v.end(), 20);
// std::distance(first,last)
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

typedef long long ll;
class Solution {
public:
    int purchasePlans(vector<int>& nums, int target) {
        ll ans = 0;
        sort(nums.begin(), nums.end());
        
        int n = nums.size();
        for(int i=0;i<n;i++){
            if(nums[i] >= target) break;
            
            int dis = target - nums[i];
            
            auto it = std::upper_bound (nums.begin(), nums.end(), dis); 
            int num = std::distance(nums.begin(), it);
            if(i < num){
                ans += num - 1;
            }else{
                ans += num;
            }
        }
        
        return ans/2 % 1000000007;
    }
};

int main() {
//   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
//   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
//   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
