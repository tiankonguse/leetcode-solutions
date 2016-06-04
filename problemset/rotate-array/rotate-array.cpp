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
    void swap(int *list, int n, int k){
        if(n <= 1 || k == 0){
            return ;
        }
        k = k % n;
        if(k == 0){
            return;
        }
        int from = k-1;
        int to = n-1;
        int left = n - k;
        int tmp;
        //printf("n=%d k=%d left=%d\n",n,k,left);
        if(left <= k){
            while(left>0){
                tmp = list[to];
                list[to] = list[from];
                list[from] = tmp;
                to--;
                from--;
                left --;
            }
            swap(list, to +1, k - (n - k));
        }else{
            while(from>=0){
                tmp = list[to];
                list[to] = list[from];
                list[from] = tmp;
                from--;
                to--;
            }
            swap(list, to+1, k);
        }
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
        swap(nums, n,n - k);
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
    int n = 6;
    int k;

    for(int k=0;k<n;k++){
        printf(">>>>>>>>>>>>>>>\n");
        bornData(n, list);
        output(n,list);
        work.rotate(list,n,k);
        printf("n=%d k=%d\n",n,k);
        output(n,list);
    }
    
    n = 7;
    for(int k=0;k<n;k++){
        printf(">>>>>>>>>>>>>>>\n");
        bornData(n, list);
        output(n,list);
        work.rotate(list,n,k);
        printf("n=%d k=%d\n",n,k);
        output(n,list);
    }
}

int main(){
    test();
    return 0;
}
