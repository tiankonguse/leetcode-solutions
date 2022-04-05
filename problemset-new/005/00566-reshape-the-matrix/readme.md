## 566. Reshape the Matrix

在 MATLAB 中，有一个非常有用的函数 reshape ，它可以将一个 m x n 矩阵重塑为另一个大小不同（r x c）的新矩阵，但保留其原始数据。

给你一个由二维数组 mat 表示的 m x n 矩阵，以及两个正整数 r 和 c ，分别表示想要的重构的矩阵的行数和列数。

重构后的矩阵需要将原始矩阵的所有元素以相同的 行遍历顺序 填充。

如果具有给定参数的 reshape 操作是可行且合理的，则输出新的重塑矩阵；否则，输出原始矩阵。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reshape-the-matrix
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


In MATLAB, there is a very useful function called 'reshape', which can reshape a matrix into a new one with different size but keep its original data.



You're given a matrix represented by a two-dimensional array, and two positive integers r and c representing the row number and column number of the wanted reshaped matrix, respectively.



The reshaped matrix need to be filled with all the elements of the original matrix in the same row-traversing order as they were.



If the 'reshape' operation with given parameters is possible and legal, output the new reshaped matrix; Otherwise, output the original matrix.





## Example 1:



```

Input: 

nums = 

[[1,2],

 [3,4]]

r = 1, c = 4

Output: 

[[1,2,3,4]]

Explanation:

The row-traversing of nums is [1,2,3,4]. The new reshaped matrix is a 1 * 4 matrix, fill it row by row by using the previous list.

```





## Example 2:





```

Input: 

nums = 

[[1,2],

 [3,4]]

r = 2, c = 4

Output: 

[[1,2],

 [3,4]]

Explanation:

There is no way to reshape a 2 * 2 matrix to a 2 * 4 matrix. So output the original matrix.

```



## Note:



1. The height and width of the given matrix is in range [1, 100].

2. The given r and c are all positive.




