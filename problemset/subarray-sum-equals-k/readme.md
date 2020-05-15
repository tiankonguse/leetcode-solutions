## 560. 和为K的子数组

### 题意


Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。  

### 样例  


输入:nums = [1,1,1], k = 2
输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。

### 说明  


1、数组的长度为 [1, 20,000]。
2、数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。


### 思路


方法一：暴力枚举  


枚举每个起始位置，循环求和，判断是否等于 k 。  
复杂度：`O(n^2)`  


方法二：统计+二分  


使用 `map<sum, vector<index>>` 预先统计所有前缀和对应的下标，下标递增有序。  
然后枚举每个起始位置 `left`， 判断 `pre_sum[left-1] + k` 是否存在，存在了，在 `vector` 中二分查找满足的个数。  


复杂度：`O(n log(n))`


```
int ans = 0;
for(int i = 0; i < nums.size(); i++){
    int target = pre_sum[i] + k;
    if(sum_to_index.count(target) == 0){
        continue;
    }

    //计算答案个数
    vector<int>& indexs = sum_to_index[target];
    auto low = std::lower_bound (indexs.begin(), indexs.end(), i);
    ans += indexs.end() - low;
}
```

方法三：前缀统计  


方法二是提前统计前缀和，然后枚举左边界，二分查找满足右边界的个数。  
如果枚举右边界的话，左边界天然就是答案个数，不需要二分了，也不需要储存下标了。  


复杂度：使用 map 时复杂度是 `O(n log(n))`，使用 unordered\_map 时，复杂度是 `O(n)`


```
for(auto v: nums){
    sum += v;
    if(m.count(sum - k)){
        ans += m[sum - k];
    }
    if(sum == k){
        ans++;
    }
    m[sum]++;
}
```


练习地址：https://leetcode-cn.com/problems/subarray-sum-equals-k/submissions/  






