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


class Solution {
public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        unordered_map<int, int> h;
        int m = target.size();
        for(int i = 0; i < m; i++){
            h[target[i]] = i + 1;
        }

        int n = 0;
        for(int i = 0; i < arr.size(); i++){
            if(h.count(arr[i]) == 0){
                continue;
            }
            arr[n++] = h[arr[i]];
        }
        arr.resize(n);

        if(n == 0){
            return m;
        }

        vector<int> dp(n + 1, m + 1);
        dp[0] = 0;
        int num = 1;
        for(int i = 0; i < n; i++){
            int pos = lower_bound(dp.begin(), dp.begin() + num, arr[i]) - dp.begin();
            dp[pos] = arr[i];
            num = max(num, pos + 1);
        }
        return m - (num - 1);
    }
};
int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
