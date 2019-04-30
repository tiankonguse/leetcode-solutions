/*************************************************************************
    > File Name: single-number-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月18日 星期六 17时30分59秒
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
    int singleNumber(int A[], int n) {
        int ones = 0;// 出现一次的标志位
        int twos = 0;// 出现第二次标志位
        for(int i = 0; i < n; i++) {
            ones = (ones ^ A[i]) & ~twos;// 第二次出现的去掉, 第一次出现的加上, 第三次出现的不变
            twos = (twos ^ A[i]) & ~ones;// 第一次出现的不变, 第二次出现的加上, 第三次出现的去掉
        }
        return ones;
    }
};

void output(int* data, int n){
    for(int i=0;i<n;i++){
        printf("%d ",data[i]);
    }
    printf("\n");
}

void bornData(vector<int>&data, int*A, int&num){
    num = data.size();
    for(int i=0;i<num;i++){
        A[i] = data[i];
    }
}

void test(){
    srand(time(NULL));
    Solution work;
    int A[100];
    vector<int>data;
    int ans;
    int num;

    data = {3,2,3,3};

    bornData(data, A, num);
    output(A, num);
    ans = work.singleNumber(A, num);
    printf("ans=%d\n",ans);
    
}

int main(){
    test();
    return 0;
}
