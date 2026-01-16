# P1013 [NOIP 1998 提高组] 进制位

## 题目描述

著名科学家卢斯为了检查学生对进位制的理解，他给出了如下的一张加法表，表中的字母代表数字。 例如：

$$
\def\arraystretch{2}
\begin{array}{c||c|c|c|c}
\rm +  & \kern{.5cm} \rm \mathclap{L} \kern{.5cm}  &  \kern{.5cm} \rm \mathclap{K} \kern{.5cm} &  \kern{.5cm} \rm \mathclap{V} \kern{.5cm} & \kern{.5cm} \rm \mathclap{E} \kern{.5cm} \\ \hline\hline
\rm L  &  \rm L  &  \rm K  &  \rm V  & \rm E  \\ \hline
\rm K  &  \rm K  &  \rm V  &  \rm E  & \rm \mathclap{KL} \\ \hline
\rm V  &  \rm V  &  \rm E  &  \rm \mathclap{KL} & \rm \mathclap{KK} \\ \hline
\rm E  &  \rm E  &  \rm \mathclap{KL} &  \rm \mathclap{KK} & \rm \mathclap{KV} \\
\end{array}$$

其含义为：

$L+L=L$，$L+K=K$，$L+V=V$，$L+E=E$

$K+L=K$，$K+K=V$，$K+V=E$，$K+E=KL$    

$\cdots$

$E+E=KV$    

根据这些规则可推导出：$L=0$，$K=1$，$V=2$，$E=3$。

同时可以确定该表表示的是 $4$ 进制加法。

## 输入格式

第一行一个整数 $n$（$3\le n\le9$）表示行数。

以下 $n$ 行，每行包括 $n$ 个字符串，每个字符串间用空格隔开。

若记 $s_{i,j}$ 表示第 $i$ 行第 $j$ 个字符串，数据保证 $s_{1,1}=\texttt +$，$s_{i,1}=s_{1,i}$，$|s_{i,1}|=1$，$s_{i,1}\ne s_{j,1}$ （$i\ne j$）。

保证至多有一组解。

## 输出格式

第一行输出各个字母表示什么数，格式如：`L=0 K=1` $\cdots$ 按给出的字母顺序排序。不同字母必须代表不同数字。

第二行输出加法运算是几进制的。

若不可能组成加法表，则应输出 `ERROR!`。

## 输入输出样例 #1

### 输入 #1

```
5
+ L K V E
L L K V E
K K V E KL
V V E KL KK
E E KL KK KV

```

### 输出 #1

```
L=0 K=1 V=2 E=3
4

```

## 说明/提示

NOIP1998 提高组 第三题