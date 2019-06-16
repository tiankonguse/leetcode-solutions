# 95. Unique Binary Search Trees II  


题意：给一个数字`n`，求构造`1~n`的所有二叉搜索树。  


思路：二叉搜索树有一个性质：左子树全部小于根，右子树全部大于根。  
对于区间`start, end`，枚举根，假设是数字`i`，则左子树就是`start~i-1`，右子树区间是`i+1~end`。  
构造的所有左子树 和 所有的右子树互相组合，就可以得到当前区间的所有二叉搜索树。  


## C++语言  


* [95-tiankonguse.cpp](./95-tiankonguse.cpp)  



