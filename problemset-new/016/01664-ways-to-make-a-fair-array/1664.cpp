// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

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

int pre[max5][2];
int sub[max5][2];

class Solution {
 public:
  int waysToMakeFair(vector<int>& nums) {
    int n = nums.size();
    pre[0][0] = pre[0][1] = 0;
    pre[n + 1][0] = pre[n + 1][0] = 0;
    for (int i = 1; i <= n; i++) {
      int v = nums[i - 1];
      pre[i][0] = pre[i - 1][0];
      pre[i][1] = pre[i - 1][1];
      if (i % 2 == 1) {
        pre[i][1] += v;
      } else {
        pre[i][0] += v;
      }
    }

    sub[0][0] = sub[0][1] = 0;
    sub[n + 1][0] = sub[n + 1][1] = 0;
    for (int i = n; i >= 1; i--) {
      int v = nums[i - 1];
      sub[i][0] = sub[i + 1][0];
      sub[i][1] = sub[i + 1][1];
      if (i % 2 == 1) {
        sub[i][1] += v;
      } else {
        sub[i][0] += v;
      }
    }

    int ans = 0;

    for (int i = 1; i <= n; i++) {
      if (pre[i - 1][0] + sub[i + 1][1] == pre[i - 1][1] + sub[i + 1][0]) {
        ans++;
      }
    }

    return ans;
  }
};