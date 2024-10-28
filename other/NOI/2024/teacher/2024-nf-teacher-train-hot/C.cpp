#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n;
vector<ll> nums;

ll ansNum = -1;
ll ansHeight = 0;
const ll maxHeight = 2000;
int main() {
  scanf("%lld", &n);
  nums.resize(maxHeight + 1, 0);
  for (int i = 0; i < n; i++) {
    ll v;
    scanf("%lld", &v);
    nums[v]++;
  }

  for (ll h = 2; h <= maxHeight * 2; h++) {  // 枚举高度
    ll tmpNum = 0;
    for (ll l = 1; l <= h/2; l++) {  // 枚举较低的木块
      ll r = h - l;
      if (r < l) break;
      if (r > maxHeight) continue;  // 不存在的木块
      if (l < r) {
        tmpNum += min(nums[l], nums[r]);
      } else if (l == r) {
        tmpNum += nums[l] / 2;
      }
    }

    if (ansNum == tmpNum) {
      ansHeight++;
    } else if (ansNum < tmpNum) {
      ansNum = tmpNum;
      ansHeight = 1;
    }
  }
  printf("%lld %lld\n", ansNum, ansHeight);

  return 0;
}