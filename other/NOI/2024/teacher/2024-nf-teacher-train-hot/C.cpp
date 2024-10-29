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


/*
比如高度H是 10，能得到多少个篱笆 O(2000)
100 个 1 和 100 个 9， 没必要循环 100 次，一次就可以知道 100 个 1 + 100 个9 可以得到 100 个 10
200 个 2 和 300 个 8， 取 200 个2 和 200 个 8，得到 200 个 10
问题0: 如何得到 100个1？ - 计数统计
问题1: 200 个 2 和 300 个 8， 取较少的。
问题1: 遍历到什么时候结束？
 - 遍历到高度？
 - 1 2 3 4 5 6 7 8 9
 - 1-9 统计后，9-1 就重复了。
 - 101个高度为5的木块，可以得到多少个篱笆  - H分奇偶性

枚举所有高度【1~4000】，得到高度的篱笆数 O(4000*2000)

第一次循环：求最多 max(【1~4000】篱笆数) O(4000)
第二次循环：求个数 sum(【1~4000】篱笆数 = max) O(4000)

同理，求出所有组合，即可求出篱笆个数


*/