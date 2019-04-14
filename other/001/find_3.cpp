/*************************************************************************
    > File Name: find_3.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年04月12日 21:13:39
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

//有多少个奇数
int full(int bit){
    int ans = 1;
    for(int i=0;i<bit;i++){
        ans = ans * 10;
    }
    return ans/2;
}

//
int fullbit(int bit){
    if(bit == 1){
        return 1;
    }
    return full(bit-1) + 10 * fullbit(bit - 1);
}



string rev(string str){
    std::reverse(str.begin(), str.end());
    return str;
}

int find3(string str){
    int ans = 0;

    if(str.length() == 1){
        return str.back() >= '3';
    }

    int height = str.back() - '0';
    str.pop_back();

    //大于3时，可以填充3，后面随便填都有3，共10^n.length()/2 个。
    if(height > 3){
        ans += full(str.length());
    }
    //0~n-1位随便填充时，对应规律：n.length() * 10^n.length()
    if(height > 0){
        ans += height * fullbit(str.length());
    }

    //此时 0 ~ n 都是答案, 有 n + 1 个
    if(height == 3){
        ans += atoi(rev(str).c_str() + 1)/2;
    }

    ans += find3(str);

    return ans;
}


int main(){
    string str = "866278171";
    printf("ans=%d\n", find3(rev(str)));
    return 0;
}
