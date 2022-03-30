/*************************************************************************
    > File Name: reverse-integer.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月06日 星期一 21时06分35秒
 ************************************************************************/

#include<stdio.h>
#include<limits.h>

typedef long long ll;

class Solution {
public:
    int reverse(int x) {
        ll X = x;
        int sign = 1;
        if(X<0){
            sign = -1;
            X = -X;
        }
        ll ans = 0;
        while(X > 0){
            ans = ans*10 + (X%10);
            X = X / 10;
        }
        ans = ans * sign;

        if(ans <  INT_MIN || ans > INT_MAX){
            return 0;
        }else{
            return (int)ans;
        }

    }
};

void test(){
    Solution work;
    int input;
    int ans;

    input = 0;
    ans = work.reverse(input);
    printf("input=%d ans=%d\n", input, ans);
    
    
    input = -1;
    ans = work.reverse(input);
    printf("input=%d ans=%d\n", input, ans);
    
    input = 1;
    ans = work.reverse(input);
    printf("input=%d ans=%d\n", input, ans);
    
    
    input = 123;
    ans = work.reverse(input);
    printf("input=%d ans=%d\n", input, ans);
    
    input = -123;
    ans = work.reverse(input);
    printf("input=%d ans=%d\n", input, ans);
    
    input = INT_MIN;
    ans = work.reverse(input);
    printf("input=%d ans=%d\n", input, ans);
    
    input = INT_MAX;
    ans = work.reverse(input);
    printf("input=%d ans=%d\n", input, ans);
    
}

int main(){
    test();
    return 0;
}
