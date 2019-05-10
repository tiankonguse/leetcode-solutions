## 4. Median of Two Sorted Arrays  


题意：给两个有序的数组，求中位数。  
如果有两个中位数，则求和除`2`。  


思路：这道题可以转化为在`[left1, right1)`和`[left2,right2)`区间内，求第`k`小的数字。  


每次求出两个区间的中位数，比如值分别是`mid1`和`mid2`,且假设`mid1 < mid2`。
如果`len(mid1) + len(mid2)>k`，那么我们可以确定答案不在`[mid2,right2)`内，此时`k`不变。
如果`len(mid1) + len(mid2)<=k`，则可以确定答案肯定不在`[left1, mid1]`内，此时`k = k - len(mid1)`。
如果其中一个数组为空了，那就是正规的二分查找了。  


依靠上面的理论，可以二分最终找到第k小的数字。


## C++语言  


[tiankonguse.cpp](./tiankonguse.cpp)


