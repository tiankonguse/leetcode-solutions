typedef long long ll;
class Solution {
 public:
  int minimumBoxes(int n) {
    ll sum = 1, num = 1, ans = 1;
    while (sum < n) {
      num++;
      ll add = (1 + num) * num / 2;
      if (sum + add <= n) {
        sum += add;
        ans += num;
        continue;
      }

      for (int i = 1; i <= num; i++) {
        ans++;
        sum += i;
        if (sum >= n) {
          return ans;
        }
      }
    }
    return ans;
  }
};