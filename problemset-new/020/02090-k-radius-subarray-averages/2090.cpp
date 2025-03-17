class Solution {
 public:
  vector<int> getAverages(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> ans(n, -1);

    vector<long long> preSum(n + 1, 0);
    for (int i = 0; i < n; i++) {
      preSum[i + 1] = preSum[i] + nums[i];
    }

    for (int i = k; i < n - k; i++) {
      int l = i - k;
      int r = i + k;
      ans[i] = (preSum[r + 1] - preSum[l]) / (r - l + 1);
    }

    return ans;
  }
};