## 旅行（travel） 

【题目描述】
乐乐要是开始他的背包旅行，这次共 𝑛𝑛 个城市，编号为1 ∼ 𝑛𝑛。乐乐从编号为 1 的城市出发，前往编号为 𝑛𝑛 的城市。
每个城市都有一件物品，重量为𝑤𝑤𝑖𝑖 ，价值为 𝑣𝑣𝑖𝑖 。
乐乐从一个城市到另一个城市，如果背包中的物品重量为 𝑎𝑎 ，行走距离为 𝑏𝑏 时，花费的体力为 𝑎𝑎 × 𝑏𝑏 ,乐乐最多只能背总重量为 𝑊𝑊 的物品。
乐乐希望到达 𝑛𝑛 时，背包中的物品价值最大，同时花费的体力最小。 
𝑛𝑛 个城市之间共 𝑚𝑚 条单向路，且无环，从一个城市出发之后，无法再回到这个城市。


## 【输入格式】


第一行3个整数𝑛𝑛, 𝑚𝑚, 𝑊𝑊。
接下来 𝑛𝑛 行，每行2个整数表示𝑤𝑤𝑖𝑖和 𝑣𝑣𝑖𝑖
接下来 𝑚𝑚 行，每行3个整数 𝑥𝑥𝑖𝑖, 𝑦𝑦𝑖𝑖, 𝑧𝑧𝑖𝑖 ,无重边，无自环。数据保证 1 可以到达 𝑛𝑛 。


## 【输出格式】

输出两个整数，表示最大值价值和获得最大值情况下最小的体力消耗。


## 【样例输入】


```
5 6 10
2 2
1 3
3 5
4 2
2 3
1 2 1
2 4 5
2 5 3
1 3 4
3 4 2
4 5 2
```

【样例输出】


```
10 20
```

## 【数据范围与提示】 

n <=1000
𝑚𝑚 ≤ 20000
𝑊𝑊 ≤ 1000
0 ≤ 𝑧𝑧𝑖𝑖 ≤ 1000
1 ≤ 𝑤𝑤𝑖𝑖, 𝑣𝑣𝑖𝑖 ≤ 1000


## 题解  


分析：  

根据 【单向路，且无环】 得知，图中不存在环，离开一个城市不可能再回到这个城市。 

但是可能存在几种无关的边，需要预处理删除

1）0 节点的入度边， n-1 节点的出边。  
2）0节点可以到达的与 n-1 节点无关的路径。
3）0节点无法到达的节点


根据【背包中的物品价值最大，同时花费的体力最小】得知，需要先保证价值最大，在这个前提下，再计算最小体力。 


故可以先计算出记录路径的最大价值。  


假设当前节点背包剩余空间 W，价值为 V。  
对于一个节点的物品，可以选择拿也可以选择不拿。  
拿了，背包剩余空间为 W-wi， 价值为 V-vi。  


状态定义： `f[n][W]` 到达节点 n 背包重量为 W 时的最优价值。  
理论复杂度：`O(n^2 W)` 
实际复杂度：`O(mW)` 对于每个边，每个权重只会计算一次 
 


计算出最大价值后，再次遍历合法的路径，计算最小代价
状态定义：`f2[n][W]` 到达节点n背包中 W 价值最优时的最小代价
复杂度：同最优价值复杂度 








