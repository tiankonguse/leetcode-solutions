# 145. Binary Tree Postorder Traversal

题意：不使用递归，后序遍历二叉树。  


思路：使用栈来代替递归。  

关键是如何判断根已经处理过了。  
一种简单的方法是将根的两个儿子指向空
另一种是使用另一个栈来储存这样的根节点
还有一种方法是自定义结构体，定义一个状态。  


## C++ 语言  


[tiankonguse.cpp](./tiankonguse.cpp)


