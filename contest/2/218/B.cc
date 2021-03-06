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


class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        long long sum = k;
        unordered_map<long long, int> m;
        int ans = 0;
        for(auto v: nums){
            long long o = sum - v;
            if(m[o] > 0){
                ans++;
                m[o]--;
            }else{
                m[v]++;
            }
        }
        return ans;
    }
};

int main() {
  return 0;
}
