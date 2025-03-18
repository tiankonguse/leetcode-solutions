# §1.1 基础

## 核心思想

我们要计算所有长度**恰好**为 k 的子串中，最多可以包含多少个元音字母。  

暴力枚举所有子串？时间复杂度是 `O(nk)`，太慢了。能否 `O(1)` 计算子串的元音个数？  

这是可以做到的，对于下图的字符串 `abci`，假如我们已经计算出了子串 `abc` 的元音个数，那么从子串 `abc` 到子串 `bci`，只需要考虑移除（离开窗口）的字母 `a` 是不是元音，以及添加（进入窗口）的字母 `i` 是不是元音即可，因为中间的字母 `b` 和 `c` 都在这两个子串中。

![lc1456.png](https://pic.leetcode.cn/1718242805-sqSjqc-lc1456.png)
## 模版


### 正常写法

```cpp
ll sum = 0, maxSum = INT_MIN;
int n = nums.size();
for (int i = 0; i < n; i++) {
  int l = i - k + 1;
  sum += nums[i];
  if (l < 0) {
    continue;
  }
  maxSum = max(maxSum, sum);
  sum -= nums[l];
}
return maxSum;
```

### 循环数组

```cpp
int ans = n + 1;
int sum = 0;
for (int i = 0; i < n + k; i++) {
  int l = i - k + 1;
  sum += nums[i % n];
  if (i < k - 1) {
    continue;
  }
  ans = min(ans, sum);
  sum -= nums[l % n]; // k == n 时，需要取模
}
return ans;
```

## 复杂度分析

* 时间复杂度：`O(n)`，其中 n 是 s 的长度。
* 空间复杂度：`O(1)`。仅用到若干额外变量。


ref: https://leetcode.cn/problems/maximum-number-of-vowels-in-a-substring-of-given-length/solutions/2809359/tao-lu-jiao-ni-jie-jue-ding-chang-hua-ch-fzfo/