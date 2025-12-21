/*
RMQ 是英文 Range Maximum/Minimum Query 的缩写，表示区间最大（最小）值。
n 个元素，Q 次询问，每次询问 [l,r] 区间最大值。  
https://oi-wiki.org/topic/rmq/

解法1：离线+单调栈
解释：所有询问按右端点排序，r 之前的入单调递减栈，二分查找，第一个大于等于 l 的是答案。  
复杂度：O(q * log(q) + q * log(n) )
https://oi-wiki.org/ds/monotonous-stack/
模版: mono-stack.cpp

解法2：sparse table
解释：预处理出 `st[i][k] = [i, i + 2^k - 1]` 区间最值
预处理： O(n log(n))  
查询： O(1)
https://oi-wiki.org/ds/sparse-table/
模版: sparse-table.cpp


解法3：线段树
解除：分治法预处理出一个区间的最值
预处理：O(n)
查询：O(log(n))
https://oi-wiki.org/ds/seg/
模版: segUpdateOne.cpp

解法4：Four Russian  
解释：分块，预处理出块内和跨块的最值
预处理：O(n log(log(n)))
查询： O(1)


*/
