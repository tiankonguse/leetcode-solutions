## 173. Binary Search Tree Iterator


实现一个二叉搜索树迭代器类BSTIterator ，表示一个按中序遍历二叉搜索树（BST）的迭代器：
BSTIterator(TreeNode root) 初始化 BSTIterator 类的一个对象。BST 的根节点 root 会作为构造函数的一部分给出。指针应初始化为一个不存在于 BST 中的数字，且该数字小于 BST 中的任何元素。
boolean hasNext() 如果向指针右侧遍历存在数字，则返回 true ；否则返回 false 。
int next()将指针向右移动，然后返回指针处的数字。
注意，指针初始化为一个不存在于 BST 中的数字，所以对 next() 的首次调用将返回 BST 中的最小元素。

你可以假设 next() 调用总是有效的，也就是说，当调用 next() 时，BST 的中序遍历中至少存在一个下一个数字。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-search-tree-iterator
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。






题意：实现一个二叉搜索树迭代器，第一次返回最小值，之后每次返回下一个最小值。  

思路：找到最小值不难，关键是找到下一个最小值。

根据二叉搜索树的性质，下一个最小值有两种可能：一种是在右子树里面；如果没有右儿子则是父节点。
找到右子树的最小值不难，关键是怎么找到父节点。

如果你学过前面的《栈和队列》文章的话，应该可以发现，可以使用栈来储存父节点路径。
这样，下一个最小值就可以轻松实现了。


## c++语言  

[tiankonguse.cpp](./tiankonguse.cpp)


