// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
  ll cost1;
  ll cost2;
  ll Solver(ll num1, ll num2) {
    num1 = num1 % mod;
    num2 = num2 % mod;
    ll c1 = (cost1 * num1) % mod;
    ll c2 = (cost2 * num2) % mod;
    return (c1 + c2) % mod;
  }
  /*
新增一层:
dis=maxVal-minVal
1) 最小值足够小 dis+1 >= n-1:   (dis+1)*cost2,  dis*cost1
2) 最小值与最大值比较接近 dis+1 < n-1: (dis+n+1)/2 * cost2 dis*cost1

*/
  pair<ll, ll> Solver2(ll n, ll maxVal, ll minVal) {
    // 枚举使用 cost1 的个数
    ll dis = maxVal - minVal;
    ll ans = dis * cost1;  // 只使用cost1
    ll ans1 = dis;
    ll ans2 = 0;
    //   printf("n=%lld maxVal=%lld minVal=%lld\n", n, maxVal,minVal);
    // printf("default ans = %lld dis = %lld ans1=%lld \n", ans, dis, ans1);
    for (ll i = 0; i < dis; i++) {  // 使用 i 个 cost1
      ll dis1 = dis - i;
      ll buf = n - 1;
      if (n % 2 == 0 && dis1 % 2 == 1) continue;  // 不存在答案
      ll newAns1 = i;
      ll newAns2 = 0;

      while (dis1 + 1 >= buf) {  // 最小值足够小
        ll num = (dis1 + 1) / buf;
        newAns2 += num * buf;
        // printf("i=%lld dis1=%lld buf=%lld num = %lld newDis1=%lld
        // newAns2=%lld\n", i, dis1, buf, num, dis1 + num - num * buf, newAns2);
        dis1 = dis1 + num - num * buf;
      }

      if (dis1 > 0) {  // 此时最小值与最大值比较接近
        if ((dis1 + n) % 2 == 0) {
          newAns2 += (dis1 + n) / 2;
        } else {
          newAns2 += (dis1 + n + n) / 2;
        }
      }

      // printf("i=%lld newAns1=%lld newAns2=%lld cost=%lld\n", i, newAns1,
      //        newAns2, newAns1 * cost1 + newAns2 * cost2);

      if (newAns1 * cost1 + newAns2 * cost2 < ans) {
        ans = newAns1 * cost1 + newAns2 * cost2;
        ans1 = newAns1;
        ans2 = newAns2;
      }
    }
    // printf("last ans = %lld n=%lld dis = %lld ans1=%lld ans2=%lld\n", ans, n,
    // dis, ans1, ans2);
    return {ans1, ans2};
  }

 public:
  int minCostToEqualizeArray(vector<int>& nums, ll cost1, ll cost2) {
    this->cost1 = cost1;
    this->cost2 = cost2;
    int n = nums.size();
    if (n == 1) return 0;

    sort(nums.begin(), nums.end());
    ll maxVal = nums.back();
    ll minVal = nums.front();
    ll sum = 0;
    for (ll v : nums) {
      sum += maxVal - v;
    }

    ll ans1 = 0, ans2 = 0;
    if (cost1 * 2 <= cost2) {  // 都选择 cost1
      ans1 += sum;
      return Solver(ans1, ans2);
    }

    ll x = maxVal - minVal;
    ll other = sum - x;
    if (x <= other) {  // 可以两两匹配
      ans2 += sum / 2;
      if (sum % 2 == 1) {
        minVal = maxVal - 1;
      } else {
        minVal = maxVal;
      }
    } else {
      ans2 += other;
      minVal = x - other;
    }

    if (minVal == maxVal) {  // 只使用 cost2 找到答案
      return Solver(ans1, ans2);
    }
    if (n == 2) {
      return Solver(ans1 + maxVal - minVal, ans2);
    }
    // 其他的都是 maxVal， 最后一个小于 maxVal

    auto [newAns1, newAns2] = Solver2(n, maxVal, minVal);
    return Solver(ans1 + newAns1, ans2 + newAns2);
  }
};