# Binary Tree Zigzag Level Order Traversa

Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).  

For example:  

Given binary tree `{3,9,20,#,#,15,7}`,  

```
    3
   / \
  9  20
    /  \
   15   7
```

return its zigzag level order traversal as:  

```
[
  [3],
  [20,9],
  [15,7]
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


## hello

建了一个小密圈，讨论各种算法群。  

![小密圈](/images/suanfa_xiaomiquan.jpg)

