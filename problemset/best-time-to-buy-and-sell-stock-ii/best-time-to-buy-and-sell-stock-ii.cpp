/*************************************************************************
    > File Name: best-time-to-buy-and-sell-stock-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月18日 星期六 17时53分05秒
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
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        int size = prices.size();
        int pre = 0;

        if(size <=1){
            return ans;
        }
        
        pre = prices[0];
        for(int i=1;i<size;i++){
            if(prices[i] > pre){
                ans += (prices[i] - pre);
                pre = prices[i];
            }else{
                pre = prices[i];
            }
        }

        return ans;
    }
};


void output(vector<int>&data){
    for(int i=0;i<data.size();i++){
        printf(" %d", data[i]);
    }
    printf("\n");
}

void test(){
    srand(time(NULL));
    Solution work;
    vector<int> data;
    int ans;

    data = {1,2,5,23,6,1,56,1};
    output(data);
    ans = work.maxProfit(data);
    printf("ans=%d\n", ans);

}

int main(){
    test();
    return 0;
}
