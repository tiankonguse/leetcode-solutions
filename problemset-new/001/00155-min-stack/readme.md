# 155 Min Stack


题意：实现一个最小栈，包含push、pop、top、getMin 四个功能。  


思路：栈的基本功能都可以使用`vector`模拟实现。  
但是，对于最小值，选择数据结构时就需要谨慎了。  


这个数据结构应该满足一下这些特征：  


1. 出栈一个数据时，需要能够快速删除这个数据。  
2. 入栈一个数据时，需要能够快速插入这个数据。  
3. 最小值出栈时，需要快速找到下一个最小值。  
4. 查询的最小值应该正确  


其中第三个特征最重要。  


大概思路是使用另外一个数据结构维护最小值。  


最简单的方法是使用 map 来查找最小值，每次操作复杂度 log(n)。  


```
map<int, int> m;  // <val, count>
stack<int> valStat;
```


另一个方法是每次将当前最小值压入另一个栈中。  


```
stack<int> minStat;
stack<int> valStat;
```



练习地址：https://leetcode-cn.com/problems/min-stack/  


详细解题报告地址：https://mp.weixin.qq.com/s/natRB_8e8sSPnkOgxDR8jg  
公众号：天空的代码世界
微信号：tiankonguse 



