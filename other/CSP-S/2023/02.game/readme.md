# 消消乐（game）

## 【题目描述】

小 L 现在在玩一个低配版本的消消乐，该版本的游戏是一维的，一次也只能消除两个相邻的元素。
现在，他有一个长度为 n 且仅由小写字母构成的字符串。
我们称一个字符串是可消除的，当且仅当可以对这个字符串进行若干次操作，使之成为一个空字符串。
其中每次操作可以从字符串中删除两个相邻的相同字符，操作后剩余字符串会拼接在一起。
小 L 想知道，这个字符串的所有非空连续子串中，有多少个是可消除的。

## 【输入格式】

从文件 game.in 中读入数据。
输入的第一行包含一个正整数 n，表示字符串的长度。
输入的第二行包含一个长度为 n 且仅由小写字母构成的的字符串，表示题目中询问的字符串。

## 【输出格式】

输出到文件 game.out 中。
输出一行包含一个整数，表示题目询问的答案。

## 【样例 1 输入】


```
8
accabccb
```

## 【样例 1 输出】

```
5
```

## 【样例 1 解释】

一共有 5 个可消除的连续子串，分别是 cc、acca、cc、bccb、accabccb。


## 【数据范围】

对于所有测试数据有：1 ≤ n ≤ 2 × 10^6，且询问的字符串仅由小写字母构成。  
特殊性质 A：字符串中的每个字符独立等概率地从字符集中选择。
特殊性质 B：字符串仅由 a 和 b 构成。


##  思路


### 暴力

枚举每个结束位置，找到前缀的所有循环节，答案就是循环节的个数。  
复杂度：`O(n^2)`  


### DP 循环枚举下一跳 优化  


令 `dp[i]` 为以 i 为结束位置的循环节个数，也是答案个数。  
找到第一个循环节的起始位置 j，则答案可以优化为 `dp[i] = dp[j-1] + 1`


如何找到 j 呢？  
定义状态：`pre[i]` 含义为循环节的起始位置。  
则 `dp[i] = dp[pre[i]-1] + 1`。  


如果 `s[i-1]==s[i]`, `pre[i] = i-1`。  
否则，需要先找到 `s[i-1]`的循环节，然后在前面判断是否和 `s[i]`相等，不等，再循环找循环节。  


```cpp
j = i
while(s[j] != v){
    j = pre[i]-1
}
pre[i] = j;
```


看起来是 `O(n^2)`，但是相同字符每个位置只会扫描一次。  
复杂度：`O(26 N)`  


## DP 枚举字符优化  


为了避免重复不断向前循环尝试匹配，可以每次循环都定义一个状态。  
定义状态：`f[i][v]` 以 i 为后缀，后面追加一个 `v`时，匹配的起始下标。 
则 `pre[i] = f[i-1][s[i]]`。  


对于 `f[i][v]`，分两种情况来看  
如果 `s[i] == v`， 则 `f[i][v]=i`  
否则，需要先找到与 `s[i]`的最小循环节，然后再往前尝试匹配 v。  


复杂度：`O(26 N)`  


## HASH 前缀差  

通过前缀可以求答案。  
解释：`H[i] == H[j]`, 则 `str[i+1,j]` 可以消除。  
此时，`str[0,i]` 与 `str[1,j]` 的匹配栈相等， 故 hash 算法需要基于匹配栈来计算。  














