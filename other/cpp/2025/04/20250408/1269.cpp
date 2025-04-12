/*
http://ybt.ssoier.cn:8088/problem_show.php?pid=1269

题目描述】
为了庆贺班级在校运动会上取得全校第一名成绩，班主任决定开一场庆功会，为此拨款购买奖品犒劳运动员。期望拨款金额能购买最大价值的奖品，可以补充他们的精力和体力。

【输入】
第一行二个数n(n≤500)，m(m≤6000)，其中n 代表希望购买的奖品的种数，m 表示拨款金额。

接下来n行，每行3个数，v、w、s，分别表示第I种奖品的价格、价值（价格与价值是不同的概念）和能购买的最大数量（买0件到s件均可），其中v≤100，w≤1000，s≤10 个。

【输出】
一行：一个数，表示此次购买能获得的最大的价值（注意！不是价格）。

【输入样例】
5 1000
80 20 4
40 50 9
30 50 7
40 30 6
20 20 1
【输出样例】
1040

*/
#include<bits/stdc++.h>
using namespace std;
int m,n;
int dp[100005]; // 修改：使用一维数组优化空间复杂度
int w[32],c[32],s[32];
int weight[32]; // 修改：更具描述性的变量名
int value[32]; // 修改：更具描述性的变量名
int main() {
    memset(dp,0,sizeof(dp));//初始化为0 
    scanf("%d%d",&n,&m);
    int index=0;
    for(int i=0; i<n; i++) {
        scanf("%d%d%d",&w[i],&c[i],&s[i]);
        //二进制优化 
        for(int k=1;k<=s[i];k=k*2){
            weight[index]=k*w[i];
            value[index]=k*c[i];
            s[i]=s[i]-k;
            index++;
        }
        if(s[i]>0){ //处理剩余 
            weight[index]=s[i]*w[i];
            value[index]=s[i]*c[i];
            index++;
        }
    }
    //01背包,此时物品的数量为index个
    //使用01背包的模板 
    for(int i=0;i<index;i++){
        for(int j=m;j>=weight[i];j--){ // 修改：优化空间复杂度，从后向前更新
            dp[j]=max(dp[j],dp[j-weight[i]]+value[i]);
        }
    }
    printf("%d\n",dp[m]);
    return 0;
}