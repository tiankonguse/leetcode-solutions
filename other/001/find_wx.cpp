/*************************************************************************
    > File Name: find_wx.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年04月12日 21:00:10
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const double PI = acos(-1.0), eps = 1e-7;
const int INF = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 4100, max4 = 11100, max5 = 200100, max6 = 2000100;
const int debug = 0;
const int inf = 0x3f3f3f3f;
#define  myprintf(fmt,args...) do{if(debug)printf(fmt, ##args);}while(0)


const int N=sqrt(0.0 + 707829217) + 1;
const int M=30000;
bool is[N];
int prm[M];
int getprm() {
    int e = (int)(sqrt(0.0 + N) + 1),k=0,i;
    memset(is, 1, sizeof(is));
    prm[k++] = 2;
    is[0] = is[1] = 0;
    for (i = 4; i < N; i += 2)
        is[i] = 0;
    for(i=3; i<e; i+=2) {
        if(is[i]) {
            prm[k++]=i;
            for(int s=i+i,j=i*i; j<N; j+=s)
                is[j]=0;
        }
    }
    for (; i < N; i += 2)
        if (is[i])
            prm[k++] = i;
    return k;
}

int main() {

    int prmNum = getprm();
    printf("prmNum = %d\n", prmNum);
    for(int i=0;i<prmNum;i++){
        if(707829217 % prm[i] == 0){
            printf("find: %d %d\n", prm[i], 707829217/prm[i]);
        }
    }

    return 0;
}
