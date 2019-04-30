/*************************************************************************
    > File Name: best-time-to-buy-and-sell-stock.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月18日 星期六 17时43分12秒
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
        int minPrice = 0;
        int ans = 0;
        int size = prices.size();

        if(size == 0){
            return ans;
        }
        minPrice = prices[0];

        for(int i=1;i<size;i++){
            if(prices[i]-minPrice > ans){
                ans = prices[i] - minPrice;
            }
            if(minPrice > prices[i]){
                minPrice = prices[i];
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
