## 1043. Partition Array for Maximum Sum


题意：给出整数数组 A，将该数组分隔为长度最多为 K 的几个（连续）子数组。  
分隔完成后，每个子数组的中的值都会变为该子数组中的最大值。
返回给定数组完成分隔后的最大和。


思路：最最基础的动态规划题。  
定义`f(n)`为前`n`个数字可以得到的最大和。  
则对于最后一个数字可以划分为两部分：

1. `[n-k+1, n]`划分为一个整体,结果为`max(n-k+1, n) * k`  
2. `[1, n-k]`递归去计算，即`f(n-k)`  

这种划分，共有`K`中情况，我们要取结果最大的那个。  
复杂度：`O(n*K)`  


思考题：这道题能继续优化吗？比如利用单调性，把复杂度优化到`O(n)`吗？  


## C++语言  

[tiankonguse.cpp](./tiankonguse.cpp)

## Python语言
[marvelous.py](./marvelous.py)


