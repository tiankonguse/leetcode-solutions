/*************************************************************************
    > File Name: best-time-to-buy-and-sell-stock-iii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月11日 星期六 18时27分31秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
using namespace std;


class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int l = prices.size();
        if(l <= 1){
            return 0;
        }
        vector<int>leftMax(l, 0);
        vector<int>rightMax(l, 0);

        int now;
        int ans = 0;
        int finalAns = 0;

        now = prices[0];

        //printf("%-3d ", now);
        for(int i=1;i<l;i++){
            if(prices[i] - now > ans){
                ans = prices[i] - now;
            }
            if(prices[i] <= now){
                now = prices[i];
            }
            leftMax[i] = ans;

            if(ans > finalAns){
                finalAns = ans;
            }
          //  printf("%-3d ", now);
        }
        //printf("\n");
        //
        now = prices[l-1];
        ans = 0;
        for(int i=l-2;i>=0;i--){
            if(now - prices[i] > ans){
                ans = now - prices[i]; 
            }
            if(prices[i] >= now){
                now = prices[i];
            }
            rightMax[i] = ans;
            if(ans > finalAns){
                finalAns = ans;
            }
        }


        for(int i=1;i<l-2;i++){
            if(leftMax[i] + rightMax[i+1] > finalAns){
                finalAns = leftMax[i] + rightMax[i+1];
            }
        }

        return finalAns;
    }
};

void test(){
    Solution work;

    srand(time(NULL));
    vector<int>str;
    int ans;

    ans = work.maxProfit(str);
    printf("ans=%d\n", ans);

    int l = 10;
    for(int i=0;i<l;i++){
        str.push_back(rand()%100);
    }
    for(int i=0;i<l;i++){
        printf("%-3d ", str[i]);
    }
    printf("\n");

    ans = work.maxProfit(str);
    printf("ans=%d\n", ans);

    str.clear();
    str.push_back(2);
    str.push_back(1);
    str.push_back(2);
    str.push_back(0);
    str.push_back(1);
    l = str.size();
    for(int i=0;i<l;i++){
        printf("%-3d ", str[i]);
    }
    printf("\n");

    ans = work.maxProfit(str);
    printf("ans=%d\n", ans);
}

int main(){
    test();
    return 0;
}
