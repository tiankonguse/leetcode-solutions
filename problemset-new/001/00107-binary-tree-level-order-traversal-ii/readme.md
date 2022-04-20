# Binary Tree Level Order Traversal II  107. 二叉树的层序遍历 II

给你二叉树的根节点 root ，返回其节点值 自底向上的层序遍历 。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).  

For example:  
Given binary tree `{3,9,20,#,#,15,7}`,  

```
    3
   / \
  9  20
    /  \
   15   7
```

return its bottom-up level order traversal as:  

```
[
  [15,7],
  [9,20],
  [3]
]
```

confused what `"{1,#,2,3}"` means?  read more on how binary tree is serialized on OJ.


OJ's Binary Tree Serialization:
The serialization of a binary tree follows a level order traversal, where '#' signifies a path terminator where no node exists below.

Here's an example:

```
   1
  / \
 2   3
    /
   4
    \
     5
```

The above binary tree is serialized as `"{1,2,3,#,#,4,#,#,5}"`.





