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
// vector/array: upper_bound(vec.begin(), vec.end(), v)
// map: m.upper_bound(v)
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);
// unordered_map / unordered_set
// 排序，小于是升序：[](auto&a, auto&b){ return a < b; })
// 优先队列 priority_queue<Node>：大于是升序
// struct Node{
//     int t;
//     bool operator<(const Node & that)const { return this->t > that.t; }
// };

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;



typedef long long ll;

class Solution {
    int Check(ll n, ll k, ll m){
        __uint128_t  ret = 1;
        __uint128_t  base = 1;
        for(int i = 1; i < m; i++){
            base *= k;
            ret += base;
            if(ret > n){
                return 1;
            }
        }

        if(ret < n){
            return -1;
        }
        return 0;

    }
public:
    string smallestGoodBase(string n_) {
        ll n = std::stol(n_);

        for(int m = 60; m > 2; m--){
            ll left = 2, right = n;
            while(left < right){
                ll mid = (left + right)/2;
                int ret = Check(n, mid, m);
                if(ret < 0){
                    left = mid + 1;
                }else if(ret  > 0){
                    right = mid;
                }else{
                     return to_string(mid);
                }
            }
        }
        return std::to_string(n - 1);
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
