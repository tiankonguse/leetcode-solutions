/*************************************************************************
    > File Name: number-of-1-bits.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月25日 星期六 17时30分28秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<stack>
#include<map>
#include<queue>
#include<vector>
#include<time.h>
using namespace std;


#ifndef uint32_t
#define uint32_t unsigned int
#endif

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans = 0;
        while(n){
            if(n%2){
                ans = ans + 1;
            }
            n = n >> 1;
        }
        return ans;
    }
};

void test(){
    srand(time(NULL));
    Solution work;

    int data;
    int ans;

    data = 11;
    ans = work.hammingWeight(data);
    printf("data=%d ans=%d\n",data, ans);


}

int main(){
    test();
    return 0;
}
