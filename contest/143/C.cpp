/*************************************************************************
    > File Name: filling-bookcase-shelves.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2019年06月30日 11:37:47
    > link:
    > No: 1105. Filling Bookcase Shelves
    > Contest: https://leetcode.com/contest/weekly-contest-143
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelf_width) {
        vector<int> dp(books.size()+1, 1000*1000);
        dp[0] = 0;
        for(int i=1;i<=books.size(); i++){
            auto& b = books[i-1];
            int w = b[0];
            int h = b[1];
            dp[i] =  dp[i-1] + h;
            for(int j=i-1;j>0;j--){
                w += books[j-1][0];
                h = max(h, books[j-1][1]);
                if(w > shelf_width)break;
                dp[i] = min(dp[i], dp[j-1] + h);
            }
        }
        return dp[books.size()];
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
    #define CLASS Solution
    #define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
