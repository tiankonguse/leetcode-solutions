/*************************************************************************
    > File Name: climbing-stairs.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月04日 星期六 10时04分25秒
 ************************************************************************/

#include<stdio.h>

/*
f(0) = 0
f(1) = 1
f(2) = 2
f(3) = f(1) + f(2) 

f(n) = f(n-1) + f(n-2)
*/
class Solution {
public:
    int climbStairs(int n) {
        if(n == 0){
            return 0;
        }
        
        if(n == 1){
            return 1;
        }
        
        if(n == 2){
            return 2;
        }

        int a = 1;
        int b = 2;
        int c;
         n = n - 2;
        while(n--){
            c = a + b;
            a = b;
            b = c;
        }
        return b;

    }
};

int main(){
    
    Solution solver;
    int n;
    while(~scanf("%d", &n)){
        printf("%d\n", solver.climbStairs(n));
    }

    return 0;
}

