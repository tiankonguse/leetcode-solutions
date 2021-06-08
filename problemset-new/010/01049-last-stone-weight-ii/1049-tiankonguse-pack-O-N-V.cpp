10#include "base.h"

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

/*
 假设已经有最优答案，这个答案可以使用括号括起来表示。
 括号展开后，会发现是 n 个数字的加加减减，目标是使结果最小。
 这样目标就转化为了，挑选若干数字，使得和与 sum/2 最接近。  
 这就是一个0/1 背包问题了。  
*/
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
      int sum = accumulate(stones.begin(),stones.end(),0);
      int n = stones.size();
      int m = sum/2;
      vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
      for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
          dp[i][j] = dp[i-1][j];
          if(j >= stones[i-1]){
            dp[i][j] = max(dp[i][j], dp[i-1][j - stones[i-1]] + stones[i-1]);
          }
          //printf("i=%d j=%d dp=%d\n", i, j, dp[i][j]);
        }
      }

      return sum -2 *  dp[n][m];
    }
};
int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
