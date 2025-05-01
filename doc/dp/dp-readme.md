# DP 模版


## 状态压缩


```cpp
vector<int> ans;
int n = nums.size(); // 位数，一般不大于 20
int N = 1 << n;
vector<vector<int>> dp(k, vector<int>(N, -1));
vector<vector<int>> path(k, vector<int>(N, -1));

// pre 已选择的状态的结果，一般很小或者没有
// mask 未选择的状态
auto dfs = [&](auto& dfs, const int pre, const int mask) {
  int& ret = dp[pre][mask];
  if (ret != -1) {
    return ret;
  }
  if (mask == 0) {
    return ret = pre == 0; // 全部选择完，计算答案
  }

  // 枚举未选择的数字
  for (int i = 0; i < nums.size(); ++i) {
    int nextPre = (pre * pow10[bits[i]] + nums[i]) % k;
    if (mask & (1 << i) && dfs(dfs, nextPre, mask ^ (1 << i))) {
      path[pre][mask] = i;
      return ret = 1;
    }
  }
  return ret = 0;
};

if (dfs(dfs, 0, N - 1) == 0) {
  return ans;
}
// 根据 path 得到最优答案
int pre = 0;
int mask = N - 1;
ans.reserve(n);
while (mask) {
  int i = path[pre][mask];
  ans.push_back(nums[i]);
  pre = (pre * pow10[bits[i]] + nums[i]) % k;
  mask ^= (1 << i);
}
```


