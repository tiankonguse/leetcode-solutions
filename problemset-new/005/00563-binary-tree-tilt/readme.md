## Binary Tree Tilt 563. 二叉树的坡度

给你一个二叉树的根节点 root ，计算并返回 整个树 的坡度 。

一个树的 节点的坡度 定义即为，该节点左子树的节点之和和右子树节点之和的 差的绝对值 。如果没有左子树的话，左子树的节点之和为 0 ；没有右子树的话也是一样。空结点的坡度是 0 。

整个树 的坡度就是其所有节点的坡度之和。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-tilt
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

Given a binary tree, return the tilt of the whole tree.



The tilt of a tree node is defined as the absolute difference between the sum of all left subtree node values and the sum of all right subtree node values. 

Null node has tilt 0.



The tilt of the whole tree is defined as the sum of all nodes' tilt.





## Example



```

Input: 

         1

       /   \

      2     3

Output: 1

Explanation: 

Tilt of node 2 : 0

Tilt of node 3 : 0

Tilt of node 1 : |2-3| = 1

Tilt of binary tree : 0 + 0 + 1 = 1

```



## Note



The sum of node values in any subtree won't exceed the range of 32-bit integer.

All the tilt values won't exceed the range of 32-bit integer






