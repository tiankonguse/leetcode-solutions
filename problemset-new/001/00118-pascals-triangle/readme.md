# 24. 118. Pascal's Triangle

给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。

题意：给一个非负数字 n，求前n行帕斯卡三角。   


思路：两种方法，一种是迭代，一种是递归。  


迭代时对两头特殊处理，中间的则由上一个数组计算得到。  
递归时先得到n-1的答案，然后只需要最后一行的答案。  


## C++语言  

[tiankonguse-loop.cpp](./tiankonguse-loop.cpp)
[tiankonguse-recursion.cpp](./tiankonguse-recursion.cpp)



