# 24. 118. 119. Pascal's Triangle II

题意：给一个非负数字 n，求第n行帕斯卡三角。   


要求：使用`O(n)`的空间复杂度。  


思路：


基本方法是使用滚动数组的思想，从第一行开始，不断在原数组上计算下一行的答案即可。  
复杂度：`O(n^2)`


对于帕斯卡三角，实际上每行的答案是固定的，且有公式可以计算得到的。  


实际上，第k行，对应的公式是`C(k,0), C(k,1), ..., C(k, k-1), C(k, k)]`  
另外，每个组合数，也可以由前一个组合数求出来：`C[k,i] = C[k,i-1]*(k-i+1)/i`  



## C++语言  

[tiankonguse-loop.cpp](./tiankonguse-loop.cpp)
[tiankonguse-cal.cpp](./tiankonguse-cal.cpp)



