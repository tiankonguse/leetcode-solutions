# Sum Root to Leaf Numbers 

给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。
每条从根节点到叶节点的路径都代表一个数字：

例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
计算从根节点到叶节点生成的 所有数字之和 。

叶节点 是指没有子节点的节点。



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sum-root-to-leaf-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

Given a binary tree containing digits from `0-9` only, each root-to-leaf path could represent a number.  

An example is the root-to-leaf path `1->2->3` which represents the number `123`.  

Find the total sum of all root-to-leaf numbers.  

For example,  


```
    1
   / \
  2   3
```

The root-to-leaf path `1->2` represents the number `12`.  

The root-to-leaf path `1->3` represents the number `13`.  

Return the sum = `12 + 13 = 25`.  








