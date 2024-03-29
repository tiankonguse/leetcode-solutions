## 106. Construct Binary Tree from Inorder and Postorder Traversal  
## 106. 从中序与后序遍历序列构造二叉树

题意：根据一棵树的中序遍历与后序遍历构造二叉树。  


思路：  


```
中序遍历 inorder = [9,3,15,20,7]
后序遍历 postorder = [9,15,7,20,3]

    3
   / \
  9  20
    /  \
   15   7
```




根据上面的数据，可以发现，后序的最后一个位置可以确定根`postorder[4]=3`。  
然后可以在中序里找到根的位置`inorder[1]=3`。  
这样，中序根前面的数据`[0,0]`就是左儿子的数据，中序根后面的数据`[2,4]`就是右儿子的数据。  
根据中序得到的两个儿子序列的长度`1与2`，也可以得到后序的两个儿子序列`[0,0],[1,3]`。  
然后分别递归计算出对应的子树。  


## C++语言 


[tiankonguse.cpp](./tiankonguse.cpp)





