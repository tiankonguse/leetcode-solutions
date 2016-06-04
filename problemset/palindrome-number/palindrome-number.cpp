/*************************************************************************
    > File Name: palindrome-number.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月06日 星期一 21时18分29秒
 ************************************************************************/

#include<stdio.h>
#include<limits.h>


class Solution {
    typedef long long ll;
    ll reverse(int x) {
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

        return ans;
    }
public:
    bool isPalindrome(int x) {
        if(x<0){
            return false;
        }
        ll y = reverse(x);
        return (x == y);
    }
};


void test(){
    Solution work;
    int input;
    int ans;

    input = 0;
    ans = work.isPalindrome(input);
    printf("input=%d ans=%d\n", input, ans);
    
    
    input = -1;
    ans = work.isPalindrome(input);
    printf("input=%d ans=%d\n", input, ans);
    
    input = 1;
    ans = work.isPalindrome(input);
    printf("input=%d ans=%d\n", input, ans);
    
    
    input = 123;
    ans = work.isPalindrome(input);
    printf("input=%d ans=%d\n", input, ans);
    
    input = -123;
    ans = work.isPalindrome(input);
    printf("input=%d ans=%d\n", input, ans);
    
    input = INT_MIN;
    ans = work.isPalindrome(input);
    printf("input=%d ans=%d\n", input, ans);
    
    input = INT_MAX;
    ans = work.isPalindrome(input);
    printf("input=%d ans=%d\n", input, ans);
    
    input = 1221;
    ans = work.isPalindrome(input);
    printf("input=%d ans=%d\n", input, ans);
    
}

int main(){
    test();
    return 0;
}
