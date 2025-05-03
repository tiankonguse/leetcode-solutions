# 1287. 有序数组中出现次数超过25%的元素

给你一个非递减的 有序 整数数组，已知这个数组中恰好有一个整数，它的出现次数超过数组元素总数的 25%。

请你找到并返回这个整数

 

示例：

输入：arr = [1,2,2,6,6,6,6,7,10]
输出：6
 

提示：

1 <= arr.length <= 10^4
0 <= arr[i] <= 10^5



## 统计法  


统计出现次数最多的数字  


```cpp
int num = 0;
int pre = -1;
int ansNum = 0;
int ansVal = -1;
for (auto v : arr) {
  if (v != pre) {
    pre = v;
    num = 0;
  }
  num++;
  if (num > ansNum) {
    ansNum = num;
    ansVal = pre;
  }
}
```

## 贪心法  

使用滑动窗口的方法来高效地检查这样的元素。  


原理：如果一个元素在数组中出现次数超过 25%，那么在数组中一定存在一个长度为 n/4 的子数组，其中包含这个元素。
算法：枚举左指针，右指针取值 +25% 的位置，判断是否相等，相等则是答案。

```cpp
int threshold = n / 4;
for (int i = 0; i < n; i++) {
  if (i + threshold < n && arr[i] == arr[i + threshold]) {
    return arr[i];
  }
}
```
