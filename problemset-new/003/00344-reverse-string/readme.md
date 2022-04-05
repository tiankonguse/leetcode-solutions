# 344. Reverse String

编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 s 的形式给出。

不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用 O(1) 的额外空间解决这一问题。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


题意：翻转一个字符串数组。  


思路：两种方法，一种是迭代，一种是递归。  

迭代是使用双指针从两头往中间移动，每次两个指针的数据进行交换，直到两个指针相遇。  
递归则是由两个指针指向首位，首位交换之后，首指针后移，尾指针前移。  


## C++语言  

[tiankonguse.cpp](./tiankonguse.cpp)
[tiankonguse-recursion.cpp](./tiankonguse-recursion.cpp)



