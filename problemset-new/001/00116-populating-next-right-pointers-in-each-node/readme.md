# 116. 填充每个节点的下一个右侧节点指针

给定一个 完美二叉树 ，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：

```
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
```

填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。

初始状态下，所有 next 指针都被设置为 NULL。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



## 方法一：相邻指针子树递归

递归的时候，把同级别下个指针带上，就可以递归了。  


## 方法二：相邻指针链表递归

递归的时候，每次合并右边儿子组成的链表，指向下个指针左儿子组成的链表。。


## 方法三：父指针递归法


如果父指针的 next 已经求出答案，则右儿子的next 为父节点 next 的左儿子。



# Populating Next Right Pointers in Each Node 



Given a binary tree  

```
struct TreeLinkNode {
    TreeLinkNode *left;
    TreeLinkNode *right;
    TreeLinkNode *next;
}
```

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.  

Initially, all next pointers are set to NULL.  

Note:  

- You may only use constant extra space.  
- You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).  


For example,  

Given the following perfect binary tree,  


```
         1
       /  \
      2    3
     / \  / \
    4  5  6  7
```


After calling your function, the tree should look like:  


```
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
```









