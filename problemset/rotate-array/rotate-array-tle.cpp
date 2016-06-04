/*************************************************************************
    > File Name: rotate-array.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月25日 星期六 17时50分29秒
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

void output(int n, int*list){
    for(int i=0;i<n;i++){
        printf("%d ",list[i]);
    }
    printf("\n");
}

class Solution {
    void rotate(int nums[], int n){
        if(n <= 1){
            return;
        }
        n--;
        int tmp = nums[n];
        while(n>0){
            nums[n] = nums[n-1]; 
            n--;
        }
        nums[0] = tmp;
    }
public:
    void rotate(int nums[], int n, int k) {
        if(n <= 1 || k == 0){
            return ;
        }
        k = k % n;
        if(k == 0){
            return;
        }
        while(k--){
            rotate(nums, n);
        }
    }
};


void bornData(int n, int* list){
    for(int i=0;i<=n;i++){
        list[i] = i;
    }
}


void test(){
    srand(time(NULL));
    Solution work;

    int list[1000];
    int n = 7;
    int k;

    for(int k=0;k<11;k++){
        printf(">>>>>>>>>>>>>>>\n");
        bornData(n, list);
        output(n,list);
        work.rotate(list,n,k);
        printf("n=%d k=%d\n",n,k);
        output(n,list);
        printf("<<<<<<<<<<<<<<<<<<<<\n");
    }
}

int main(){
    test();
    return 0;
}
