## 题意

告诉你两个字符串s1和s2，问是否有一个s1的排列是s2的子串。  

## 思路

1. 拆解：枚举s2的所有长度为len(s1)的子串，判断是否满足。
2. 求解：对于其中一个len(s1)长度的子串，如果s1满足，则两个串的字母以及个数应该完全一致。  
3. 统计优化：假设S(i,j)是长度为len(s1)的子串，且字母统计好了，则S(i+1, j+1)可以使用O(1)的方法计算出字母统计。
4. 比较优化：假设S(i,j)与s1的比较差值与不同字母个数已经统计，则S(i+1, j+1)与s1的字母统计是否相同可以O(1)得到。  
5. 总结：加上两个优化，可以扫描一遍s2就得到答案。

## 注意事项

1. len(s2)<len(s1)是直接返回不满足  



## 代码

见[github](https://github.com/tiankonguse/leetcode-solutions/tree/master/problemset/permutation-in-string)


## hello

建了一个小密圈，讨论各种算法群。  

![小密圈](../../suanfa_xiaomiquan.jpg)