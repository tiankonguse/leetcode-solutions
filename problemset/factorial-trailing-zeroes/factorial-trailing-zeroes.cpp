/*************************************************************************
    > File Name: factorial-trailing-zeroes.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月25日 星期六 23时43分12秒
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


class Solution {
public:
    int trailingZeroes(int n) {
        int ans = 0;
        while(n){
            ans += n/5;
            n = n/5;
        }
        return ans;
    }
};

void test(){
    srand(time(NULL));
    Solution work;
    int data;
    int ans;

    data = 4;
    ans = work.trailingZeroes(data);
    printf("data=%d ans=%d\n",data, ans);


    data = 5;
    ans = work.trailingZeroes(data);
    printf("data=%d ans=%d\n",data, ans);

    data = 14;
    ans = work.trailingZeroes(data);
    printf("data=%d ans=%d\n",data, ans);

    data = 25;
    ans = work.trailingZeroes(data);
    printf("data=%d ans=%d\n",data, ans);

}

int main(){
    test();
    return 0;
}
