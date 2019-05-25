# 24. Swap Nodes in Pairs

题意：给一个链表，交换相邻的两个节点。   


思路：两种方法，一种是迭代，一种是递归。  


迭代时需要维护一个父指针，因为交换当前两个节点后，父指针的next就变化了。  
递归时只需要将返回的指针赋值给第一个节点，第一个节点指向第二个节点，返回第二个节点即可。  


## C++语言  

[tiankonguse-loop.cpp](./tiankonguse-loop.cpp)
[tiankonguse-recursion.cpp](./tiankonguse-recursion.cpp)



