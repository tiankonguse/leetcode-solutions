/*
# P1115 最大子段和

## 题目描述

给出一个长度为 $n$ 的序列 $a$，选出其中连续且非空的一段使得这段和最大。

## 输入格式

第一行是一个整数，表示序列的长度 $n$。

第二行有 $n$ 个整数，第 $i$ 个整数表示序列的第 $i$ 个数字 $a_i$。

## 输出格式

输出一行一个整数表示答案。

## 输入输出样例 #1

### 输入 #1

```
7
2 -4 3 -1 2 -4 3
```

### 输出 #1

```
4
```

## 说明/提示

#### 样例 1 解释

选取 $[3, 5]$ 子段 $\{3, -1, 2\}$，其和为 $4$。

#### 数据规模与约定

- 对于 $40\%$ 的数据，保证 $n \leq 2 \times 10^3$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 2 \times 10^5$，$-10^4 \leq a_i \leq 10^4$。
*/
#include<bits/stdc++.h>
using namespace std;
int a[300000];
int ans=0;
int max(int a,int b,int c) { //求三个数的最大值
	if(a>b&&a>c)
		return a;
	else if(b>a&&b>c)
		return b;
	else
		return c;
}
int crosfind(int a[],int left,int mid,int right) { //中间区域最大和
//计算中间位置mid往左的最大和
	int lefts=INT_MIN; //左边最大和初始值
	int s1=0;//左边序列和
	for(int i=mid; i>=left; i--) {
		s1+=a[i];
		if(s1>lefts) {
			lefts=s1;
		}
	}
//计算中间位置mid+1往右的最大和
	int rights=INT_MIN; //右边最大和初始值
	int s2=0;//右边序列和
	for(int i=mid+1; i<=right; i++) {
		s2+=a[i];
		if(s2>rights) {
			rights=s2;
		}
	}
	return lefts+rights;
}
int maxfind(int a[],int left,int right) {
	if(left==right) {
		return a[left];
	}
	int mid=(left+right)/2;
	int left_max=maxfind(a,left,mid); //左区间最大和
	int right_max=maxfind(a,mid+1,right); //右区间最大和
	int mid_max=crosfind(a,left,mid,right); //中间区间最大和
	return max(left_max,right_max,mid_max); //返回三个和中最大的
}
int main() {
	freopen("P1115_2.in","r",stdin);
	freopen("1.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=0; i<n; i++)
		scanf("%d",&a[i]);
	ans=maxfind(a,0,n-1);
	printf("%d\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
