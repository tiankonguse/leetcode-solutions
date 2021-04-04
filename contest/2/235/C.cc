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

typedef long long ll;

class Solution {
    ll dis(ll a, ll b){
        if(a > b){
            return a - b;
        }else{
            return b - a;
        }
    }
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        set<int> s;
        
        ll base = 0;
        for(int i=0;i<n;i++){
            base += dis(nums1[i], nums2[i]);
            s.insert(nums1[i]);
        }
        
        
        ll ans = base;
        
        for(int i=0;i<n;i++){
            int v = nums2[i];
            auto it = s.lower_bound(v);
            if(it == s.end()){
                // 没找到，取最后一个
                it--;
            }
            
            // 第一个大于等于的
            ll tmp = base - dis(nums1[i], nums2[i]) + dis(*it, nums2[i]) ;
            if(tmp < ans){
                ans = tmp;
            }
            
            //小于等于的
            if(it != s.begin()){
                it--;
            }
            tmp = base - dis(nums1[i], nums2[i]) + dis(*it, nums2[i]) ;
            if(tmp < ans){
                ans = tmp;
            }
        }
        
        return ans % 1000000007;
        
    }
};

int main() {
//   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
//   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
//   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
