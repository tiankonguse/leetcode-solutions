# 117. Populating Next Right Pointers in Each Node II  


题意：给定一个二叉树，填充它的每个 next 指针，让这个指针指向其下一个右侧节点。  
如果找不到下一个右侧节点，则将 next 指针设置为 NULL。  


要求：只能使用常量级额外空间。  


思路：


初步看这道题的时候，会遇到一个难题：怎么找到同一层的第一个节点，以及怎么通过通常的一个节点找到下一个节点。  


如果可以使用队列，直接 BFS 搜索即可。  
但是只能使用常量级别的额外空间，这就需要观察答案的特征了。  


简单观察，可以发现假设上一层的`next`已经全部求出来了，我们只需要遍历上一层的链表，就可以找到下一层的第一个节点。  继续遍历，则可以找到下一个节点。  
所以这道题可以通过上层的`next`链表来求出下层的`next`链表，直到求出所有层的`next`。  


复杂度：`O(N)`  


## C++语言


[tiankonguse.cpp](./tiankonguse-que.cpp)
[tiankonguse.cpp](./tiankonguse.cpp)


