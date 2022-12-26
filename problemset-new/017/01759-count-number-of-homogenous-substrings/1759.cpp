#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
  ll Cal(ll n) { return (1 + n) * n / 2 % mod; }

 public:
  int countHomogenousV1(const string& s) {
    ll ans = 0;
    char pre = ' ';
    ll num = 0;
    for (auto c : s) {
      if (c != pre) {
        ans = (ans + Cal(num)) % mod;
        num = 0;
      }
      num++;
      pre = c;
    }
    ans = (ans + Cal(num)) % mod;
    return ans;
  }

  int countHomogenous(const string& s) {
    ll ans = 0;
    char pre = ' ';
    ll num = 0;
    for (auto c : s) {
      if (c != pre) {
        num = 0;
      }
      num++;
      ans = (ans + num) % mod;
      pre = c;
    }
    return ans;
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
