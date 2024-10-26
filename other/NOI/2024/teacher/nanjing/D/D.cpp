#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int nums[N];
unordered_set<int> H;
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
  }
  int ans = 1;
  int r = 0;  // [l,r)
  for (int l = 0; l < n; l++) {
    // 找到以 l 为起始位置，最长的 [l,r)，且不含重复项
    while (r < n && H.count(nums[r]) == 0) {
      H.insert(nums[r]);
      r++;
    }
    ans = max(ans, r - l);
    H.erase(nums[l]);
  }

  printf("%d\n", ans);

  return 0;
}