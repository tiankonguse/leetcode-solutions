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
  int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
 public:
  int countDifferentSubsequenceGCDs(vector<int>& nums) {
    int max_val = 0;
    for (const auto v : nums) {
        max_val = max(max_val, v);
    }
      
    vector<bool> is;
    is.resize(max_val+1, false);
    for (const auto v : nums) {
       is[v] = true;
    }
    
    int ans = 0;
    for(int i=1;i<=max_val;i++){
        int gcd_val = 0;
        for(int j = i; j <= max_val; j+=i){
            if(!is[j]) continue;
            
            if(gcd_val == 0){
                gcd_val = j;
            }else{
                gcd_val = gcd(gcd_val,  j);
            }
        }
        if(gcd_val == i){
            ans++;
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
