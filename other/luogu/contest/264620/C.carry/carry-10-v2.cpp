#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int medule = 998244353;

// 模拟计算 C(l,r)：区间A[l]~A[r]依次累加，统计总进位次数

ll jinwei(const vector<ll>& A, int l, int r) {
  ll S = 0;
  ll cnt = 0;
  for (int i = l; i <= r; i++) {
    ll num = A[i];
    ll t = num;
    ll c = 0;  // 当前这一次加法的进位
    // 从低位到高位，逐位模拟二进制加法，最多40位足够
    for (int j = 0; j <= 40; j++) {
      int x = (S >> j) & 1;
      int y = (t >> j) & 1;
      int total = x + y + c;
      if (total >= 2) {
        c = 1;
        cnt++;  // 产生一次进位，计数+1
      } else {
        c = 0;
      }
    }
    S = S + num;
  }
  return cnt;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<ll> A(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> A[i];
    }
    vector<ll> dp(n + 1, 0);  // dp[i]表示以第i个下标为结尾的合法序列数
    ll ans = 0;
    // 从小到大枚举 i, 复杂度(n)
    // A[i], A[i+1], A[i+2],... 
    // 问题： A[i]+A[i+1]+... 加到哪些位置，只进一位
    // jinwei(i, k1) <= jinwei(i, k2), k1<k2
    // 0 , 0, 0, 1 , 1, 1, 2, 2, ...
    // 二分找到第一个 1 的位置 k1，二分找到最后一个 1 的位置 k2, 复杂度 O(log(n))
    // dp[k1] += dp[i];
    // dp[...] += dp[i];
    // dp[k2] += dp[i];
    // 二分, L=i, R=n, mid = (L+R)/2;
    // 问题1）怎么快速求出 jinwei(i, mid) 的值
    //    1) 模拟 A[i]+A[i+1]+...+A[mid]，复杂度 O(n) --- 超时
    //    2) 前缀和统计bit位的个数，复杂度 O(log(n))
/*

jinwei(i, mid) 的值

1: 0001
2: 0001
3: 0001
4: 0001
...

第1位：4个1
第2位：0个1
第3位：0个1
第4位：0个1

前缀和：求出 第i个数到第mid个数各位1的个数

*/
    // 问题2）怎么批量对 dp[k1]~dp[k2] 批量加上 dp[i]? 
    //    1)线段树 O(log(n)) 
    //    2)树状数组 O(log(n)) 
    //    3) 差分+前缀和 sum(i) = sum(i-1) + val[i]， 复杂度O(1)


    // for (int l = 1; l <= n; l++) {
    //   dp[i] = 1;  // 单独[i]这个序列，基础是1
    //   // 枚举所有j < i，判断C(j,i)是否等于1 ,，枚举的子序列
    //   for (int j = 1; j < i; j++) {
    //     //优化思路：分析 [1,i-1] 这些下标 jinwei(A, j, i) 的值的特征
    //     // 特征：二分找到所有 jinwei(A, j, i)=1 的下标
    //     ll c = jinwei(A, j, i);
    //     if (c == 1) {
    //       dp[i] = (dp[i] + dp[j]) % medule;
    //     }
    //   }
    //   ans = (ans + dp[i]) % medule;
    // }
    cout << ans << endl;
  }
  return 0;
}