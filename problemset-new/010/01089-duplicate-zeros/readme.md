# 1089. Duplicate Zeros


题意：给一个数组，如果数组某个位置值是`0`，则在其后面插入一个`0`，后面的元素整体后移。  
要求：数组的长度不能变化。  


思路：这里数组长度不能变化的意思就是，每插入一个`0`，最后一个元素就需要从数组中删除。  


比赛期间，最简单粗暴的方法就是定义一个新的数组，循环处理即可。  
如果作为面试题，要求`O(1)`空间与`O(n)`时间，那就需要预处理，预先计算出要插入多少个`0`，并计算出最终的最后一个位置。  
有一个注意点是，有可能最后一个位置是`0`，刚好长度不够，最后一个`0`可能不需要插入`0`。  
这种情况特殊判断即可。  




## C++语言 

* [1089-tiankonguse.cpp](./1089-tiankonguse.cpp)
