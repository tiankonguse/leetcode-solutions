/*************************************************************************
    > File Name: sqrtx.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月11日 星期六 17时53分24秒
 ************************************************************************/

#include<stdio.h>

class Solution {
public:
    int sqrt(int x) {
        if(x<=0){
            return 0;
        }
        long long xx = x;
        long long l=1,r=x,m;
        long long tmp;
        while(l<r){
            m = (l+r)/2;
            tmp = m*m;

//            printf("x=%d l=%d r=%d m=%d tmp=%d\n",x, l,r,m,tmp);
            if(tmp == x){
                return m;
            }else if(tmp > x){
                r = m - 1;
            }else if(tmp < x){
                l = m + 1;
            }
        }
        if(l*l > x){
            return l - 1;
        }else if(l*l <= x){
            return l;
        }
        
    }
};

void test(){
    Solution work;
    int x;
    for(x=0;x<33;x++){
        printf("x=%d ans=%d\n", x, work.sqrt(x));
    }
    x = 2147395599;
    printf("x=%d ans=%d\n", x, work.sqrt(x));

}

int main(){
    test();
    return 0;
}
