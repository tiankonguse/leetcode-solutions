/*************************************************************************
    > File Name: reverse-bits.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月25日 星期六 17时39分02秒
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

const int L = 32;

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        for(int i=0;i<L;i++){
            ans = (ans<<1) | (n&1);
            n = n >> 1;
        }
        return ans;
    }
};


void test(){
    srand(time(NULL));
    Solution work;

    uint32_t data;
    uint32_t ans;

    data = 43261596;
    ans = work.reverseBits(data);
    printf("data=%u, ans=%u\n", data, ans);

}

int main(){
    test();
    return 0;
}
