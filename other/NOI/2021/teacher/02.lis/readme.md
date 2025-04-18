# 序列（lis） 

## 【题目描述】

有 𝑛𝑛 个不相同的整数组成的数列，记为: 𝑎𝑎�1�, 𝑎𝑎�2�, … … , 𝑎𝑎(𝑛𝑛)，例如：3，18，7，14，10，12，23，41，16，24。 
上例中挑出：3，18，23，24就是一个长度为4的上升序列，
如果挑出： 3，7，10，12，16，24长度为6的上升序列。
求出最长的上升序列的长度。



## 【输入格式】


第一行一个整数𝑛𝑛(1 <= 𝑛𝑛 <= 1000)
第二行为 𝑛𝑛 个空格隔开的整数。

## 【输出格式】

最长上升子序列的长度。


## 【样例输入】

```
10
3 18 7 14 10 12 23 41 16 24
```

## 【样例输出】 


```
6
```

## 【数据范围与提示】


10%数据，如样例所述；
数据点2中，输入的20个整数严格上升；
数据点3中，输入的20个整数严格下降；
数据点4中，输入的1000个整数相等；
数据点5中，𝑛𝑛 <= 10；
数据点6~10无特殊限制，1 <= 𝑛𝑛 <= 1000。


## 题解

动态规划。  


思路1：基本动态规划
状态定义: `f[n]` 以 n 为结尾的最长上升序列长度。  
状态转移方程: `f[n] = max(f[i], i<n && V[i]<V[n]) + 1`
复杂度：`O(n^2)`  


思路2：
状态定义: `f[k]` 目前为止， 最长上升序列长度为 k 的最小值。  

方程： `f[P] = min(f[P], V), P=Count(sum[f[0], f[n]]<V)`
特征：f 是一个单调递增序列
对于新来的一个数字 V，二分查找找到小于 V 的个数 P，则该数组的最长上升序列长度为 P + 1
判断当前 V 是否可以更新到 P+1 位置里。  



