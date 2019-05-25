# 344. Reverse String

题意：翻转一个字符串数组。  


思路：两种方法，一种是迭代，一种是递归。  

迭代是使用双指针从两头往中间移动，每次两个指针的数据进行交换，直到两个指针相遇。  
递归则是由两个指针指向首位，首位交换之后，首指针后移，尾指针前移。  


## C++语言  

[tiankonguse.cpp](./tiankonguse.cpp)
[tiankonguse-recursion.cpp](./tiankonguse-recursion.cpp)



