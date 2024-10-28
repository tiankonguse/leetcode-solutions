#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n;
vector<ll> nums;

ll ansNum = -1;
ll ansHeight = 0;

int main() {
  scanf("%lld", &n);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
  }
  sort(nums.begin(), nums.end());

  const ll maxHeight = nums[n - 1] + nums[n - 2];
  const ll minHeight = nums[0] + nums[1];
  for (ll h = minHeight; h <= maxHeight; h++) {
    int l = 0, r = n - 1;
    ll tmpNum = 0;
    while (l < r) {
      if (nums[l] + nums[r] == h) {
        tmpNum++;
        l++;
        r--;
      } else if (nums[l] + nums[r] > h) {
        r--;
      } else if (nums[l] + nums[r] < h) {
        l++;
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