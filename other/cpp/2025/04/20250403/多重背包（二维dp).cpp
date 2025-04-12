#include<bits/stdc++.h>
using namespace std;
const int N=500;
const int M=5000;
int cap[M]; //物品的容量
int val[M]; //物品的价值
int dp[32][205];
int index=0;
int maxvalue(int i,int j) {
	if(dp[i][j]!=-1) { //已经计算过
		return dp[i][j];
	}
	//边界条件
	if(i==0||j==0) {
		dp[i][j]=0;
		return dp[i][j];
	}
	//状态转移方程
	//不放第i件物品
	if(cap[i-1]>j) { //不可以放
		dp[i][j]=maxvalue(i-1,j);
	}
	//如果可以放
	else {
		dp[i][j]=max(dp[i][j],maxvalue(i-1,j-cap[i-1])+val[i-1]);
	}
	return dp[i][j];
}
int main() {
	int n,m;
	int v,w,s,k;
	memset(dp,-1,sizeof(dp));
	scanf("%d%d",&n,&m);
	for(int i=0; i<n; i++) {
		scanf("%d%d%d",&v,&w,&s);  //输入一种物品的容量，价值，数量
		//二进制优化分解
		for(k=1; k<=s; k++) {
			cap[index]=k*v;
			val[index]=k*w;
			index++;
			s=s-k;
		}
		//如果还有剩余,直接把剩下的打包为一个
		if(s>0) {
			cap[index]=s*v;
			val[index]=s*w;
			index++;
		}
	}
	//01背包,此时物品的件数为index件
	int ans=maxvalue(index,m);
	printf("%d\n",ans);
	return 0;
}
