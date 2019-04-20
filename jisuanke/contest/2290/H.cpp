/*************************************************************************
    > File Name: H.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat Apr 20 12:07:49 2019
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T> >;
template <class T>
using max_queue = priority_queue<T>;

typedef long long LL;
const double PI = acos(-1.0), eps = 1e-7;
const int INF = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 4100, max4 = 11100, max5 = 200100, max6 = 2000100;
const int debug = 0;
const int inf = 0x3f3f3f3f;
#define  myprintf(fmt,args...) do{if(debug)printf(fmt, ##args);}while(0)

LL muti_mod(LL a,LL b,LL c) {
    a%=c;
    b%=c;
    LL ret=0;
    while (b) {
        if (b&1) {
            ret+=a;
            if (ret>=c)
                ret-=c;
        }
        a<<=1;
        if (a>=c)
            a-=c;
        b>>=1;
    }
    return ret;
}

LL pow_mod(LL x,LL n,LL mod) {
    if (n==1)
        return x%mod;
    int bit[64],k=0;
    while (n) {
        bit[k++]=n&1;
        n>>=1;
    }
    LL ret=1;
    for (k=k-1; k>=0; k--) {
        ret=muti_mod(ret,ret,mod);
        if (bit[k]==1)
            ret=muti_mod(ret,x,mod);
    }
    return ret;
}

int main() {
//#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
//    if(debug == 0)
//        freopen("out.txt", "w", stdout);
//#endif


    int n;
    scanf("%d", &n);
    if(n == 1){
        printf("%d\n", 1);
    }else{
        printf("%lld\n",muti_mod(pow_mod(3, n-2, 1000000007), 4, 1000000007));
    }

    return 0;
}
