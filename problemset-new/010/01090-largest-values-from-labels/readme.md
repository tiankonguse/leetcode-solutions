# 1090. Largest Values From Labels  


题意：给一个集合，每个元素有一个值`values[i]`与标签`labels[i]`。  
这里要选择一个子集，使得子集的元素个数不超过`num_wanted`，而且相同标签的元素个数不超过`use_limit`。  
求子集的最大和。  


思路：这里第一步是要读懂题意，我反复读了十遍题目，结合数据样例终于看懂题了。  


关键点在于这句话`For every label L, the number of items in S with label L is <= use_limit.`。  
含义是子集里面，相同的标签有一个个数限制，即不超过`use_limit`个。  


题意理解了，代码就好做了。  
一种方法是先使用`map`对标签进行聚合，相同标签的元素，按`value`值从大到小排序。  
然后对于每个标签，选出`top use_limit`大的值，选出的所有值里面再选择最大的`num_wanted`个。  


具体代码实现的时候，我定义了一个节点结构体，然后二维排序。  
然后遍历排序后的数据，对每个标签挑选出`top use_limit`的元素放入到优先队列里面，最后从优先队列里面取`num_wanted`个最大值即可。  




## C++语言  


* [1090-tiankonguse.cpp](./1090-tiankonguse.cpp)  

