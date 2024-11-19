#include <bits/stdc++.h>
#define LOCAL_MAIN 1

#include "3351.cpp"
using namespace std;

int main() {
  int n;
  vector<int> nums;
  scanf("%d", &n);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
  }

  Solution s;
  int ans = s.sumOfGoodSubsequences(nums);
  printf("%d\n", ans);
  return 0;
}
