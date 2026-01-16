# P1548 [NOIP 1997 普及组] 棋盘问题

## 题目背景

NOIP1997 普及组第一题

## 题目描述

设有一个 $N \times M$ 方格的棋盘 $(1≤N≤100,1≤M≤100)$

求出该棋盘中包含有多少个正方形、多少个长方形（不包括正方形）。

例如：当 $N=2, M=3$ 时：

![](https://cdn.luogu.com.cn/upload/image_hosting/kkidop2i.png)

   
正方形的个数有 $8$ 个：即边长为 $1$ 的正方形有 $6$ 个；边长为 $2$ 的正方形有 $2$ 个。

长方形的个数有 $10$ 个：

即  

- $2 \times 1$ 的长方形有 $4$ 个：

![](https://cdn.luogu.com.cn/upload/image_hosting/vhazon60.png)

- $1 \times 2$ 的长方形有 $3$ 个：  

![](https://cdn.luogu.com.cn/upload/image_hosting/jr40fqzv.png)

- $3 \times 1$ 的长方形有 $2$ 个：  

![](https://cdn.luogu.com.cn/upload/image_hosting/ja0mx48f.png)

- $3 \times 2$ 的长方形有 $1$ 个：  

![](https://cdn.luogu.com.cn/upload/image_hosting/kkidop2i.png)

## 输入格式

一行两个整数 $N,M$。

## 输出格式

一行两个整数，表示正方形的个数与长方形的个数。

## 输入输出样例 #1

### 输入 #1

```
2 3
```

### 输出 #1

```
8 10
```