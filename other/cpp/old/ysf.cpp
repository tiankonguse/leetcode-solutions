/*
ID: tiankonguse
TASK: yuesefu
LANG: C++
*/
#define TASK "yuesefu"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void Solver() {  //
  ll n, m;
  scanf("%lld%lld", &n, &m);
  vector<ll> nums(n);
  for (int i = 0; i < n; i++) {
    nums[i] = i + 1;
  }

  ll count = 1;
  ll index = 0;
  while (nums.size() > 1) {
    if (count == m) {  // 当前是第 m 个人了，删除
      printf("delete: %lld\n", nums[index]);
      nums.erase(nums.begin() + index);

      // 删除之后，之后的数据前移一位，下标不变，计数器重置
      index = index;
      count = 1;
    } else {
      index++;
      count++;
    }

    // 游标后移之后，需要检查是否到达最后
    if (index == nums.size()) {
      index = 0;
    }
  }
  printf("last=%lld\n", nums[0]);
}

int main() {
  Solver();
  return 0;
}

/*

*/