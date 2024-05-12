
typedef long long ll;
class Solution {
  int n;
  int MASK;
  vector<int> nums;
  vector<vector<vector<pair<int, int>>>> dp;
  pair<int, int> Dfs(const int k, const int mask, const int l, const int r) {
    auto& p = dp[mask][l][r];
    if (p.second != INT_MAX) return p;

    for (int i = 0; i < n; i++) {
      // 枚举最后一个数字为第 i
      if (((mask >> i) & 1) == 0) continue;
      if (k == 1) {  // 最后一个数字
        p.first = abs(l - nums[i]) + abs(i - nums[r]);
        p.second = i;
        return p;
      }

      auto ret = Dfs(k - 1, mask ^ (1 << i), i, r);
      int cost = ret.first + abs(l - nums[i]);
      if (cost < p.first || (cost == p.first && i < p.second)) {
        p.first = cost;
        p.second = i;
        // printf("mask=%d l=%d r=%d -> {%d, %d}\n", mask, l, r, p.first,
        //        p.second);
      }
    }
    return p;
  }

 public:
  vector<int> findPermutation(vector<int>& nums_) {
    nums.swap(nums_);
    n = nums.size();
    MASK = (1 << n) - 1;
    dp.resize(1 << n, vector<vector<pair<int, int>>>(
                          n, vector<pair<int, int>>(n, {INT_MAX, INT_MAX})));

    pair<int, int> p = {INT_MAX, INT_MAX};
    for (int i = 0; i < 1; i++) {  //
      auto ret = Dfs(n - 1, MASK ^ (1 << i), i, i);
      if (ret.first < p.first || (ret.first == p.first && ret.second < p.second)) {
        p.first = ret.first;
        p.second = i;
      }
    }

    // printf("ans last={%d, %d}\n", p.first, p.second);
    vector<int> ans;
    ans.push_back(p.second);
    int mask = MASK ^ (1 << p.second);
    int l = p.second;
    int r = p.second;
    int k = n - 1;

    while (k) {
      auto& p = dp[mask][l][r];
      ans.push_back(p.second);
      mask = mask ^ (1 << p.second);
      l = p.second;
      k--;
    }
    // std::reverse(ans.begin(), ans.end());
    return ans;
  }
};