/*************************************************************************
    > File Name: happy-number.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月25日 星期六 17时11分45秒
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
    map<int, int>m;

    int happy(int n){
        int ans = 0;
        int d;
        while(n){
            d = n % 10;
            ans += d * d;
            n = n / 10;
        }
        return ans;
    }

    int debug;
public:
    Solution(int debug=0):debug(debug){

    }
    bool isHappy(int n) {
        m.clear();
        int next;
        if(debug){
            printf("%d->", n);
        }
        while(m.find(n) == m.end()){
            next = happy(n);
            if(debug){
                printf("%d->", next);
            }
            if(next == 1){
                if(debug){
                    printf("  %d\n",next);
                }
                return true;
            }
            m[n] = next;
            n = next;
        }
        if(debug){
            printf(" %d\n", n);
        }
        return false;
    }
};



void test(){
    srand(time(NULL));
    Solution work(1);

    int ans;
    int data;

    data = 19;
    ans = work.isHappy(data);
    printf("n = %d ans = %d\n", data, ans);
    
    for(int i=1;i<10;i++){
        data = i;
        ans = work.isHappy(data);
        printf("n = %d ans = %d\n", data, ans);
    }
}

int main(){
    test();
    return 0;
}
