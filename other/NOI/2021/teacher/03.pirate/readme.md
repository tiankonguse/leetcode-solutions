# 海贼王（pirate） 

【题目描述】
总所周知，动漫《海贼王》里有许多大海贼团，他们每个人都在海上有一定的领地。
今天世界政府想要评估一下当下海贼的势力值。
为了简化计算，做如下设定，每个海贼团作为一个节点，单个海贼团有其威望值 𝑎𝑎𝑖𝑖 。
当其作为整个海贼组织的领袖——海贼王时，对于海上的海贼势力值计算为`sum(dist(i,v)*a)`其中v表示当选海贼王的海贼团，dist(i , 𝑣𝑣)
在海上 海贼团距离当前v海贼团的距离，其中这里的距离规定如果两个海贼团相连且有海路，则这两个海贼团之间距离为 1 。
任意两个海贼团之间只有一条通路。
所以请你帮帮当下政府计算下所需要面对的海贼最大势力值为多少。


## 【输入格式】


第一行输入一个数𝑛𝑛(1 <= 𝑛𝑛 <= 2 ∗ 10^5),表示当下海贼团数量。
第二行输入 𝑛𝑛 个数字 𝑎[i] 表示每个海贼团的威望值(1 <= 𝑎[i] <= 5∗10^5)。
接下来的 𝑛𝑛 − 1 行，每行输入𝑢𝑢, 𝑣𝑣(1 <= 𝑢𝑢, 𝑣𝑣 <= 𝑛𝑛) 𝑢𝑢, 𝑣𝑣 不同,表示𝑢𝑢, 𝑣𝑣两个海贼团之间有一条海路。


## 【输出格式】

输出当下海贼最大势力值。


## 【样例输入】

```
8
9 4 1 7 10 1 6 5
1 2
2 3
1 4
1 5
5 6
5 7
5 8
```


## 【样例输出】

```
121
```


## 【数据范围与提示】 


对于 50% 数据 ，1 <= 𝑛𝑛 <= 10000, 1 <= 𝑎𝑎[i] <= 5 ∗ 10^5
对于 100% 数据，1 <= 𝑛𝑛 <= 2 ∗ 10^5, 1 <= 𝑎𝑎[i] <= 5 ∗ 10^5



## 题解  

  


分析：

任意两个海贼团之间只有一条通路， 说明图是一个无向无根树。

假设任一一点为根时，各个节点的答案为 `dist(i,v)*ai`。  
根转移到相邻节点时，被选择的节点所在子树上的节点距离新的根的距离都减1，势力值需要减去子树的节点和为 sum(i)。  
同理，未被选择的节点距离新的根的距离都加1，势力值需要加上其他节点和`sum - sum(i)`。  


算法：随便选择一个顶点当做根，预处理出各个子树的节点和 和 势力值。  
之后递归的将根转移到相邻节点，求出相邻节点为根时的势力值。  
最后，所有势力值求最大值。  




