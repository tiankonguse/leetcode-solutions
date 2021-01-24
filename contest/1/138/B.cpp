/*************************************************************************
    > File Name: 1052-grumpy-bookstore-owner.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 26 10:08:23 2019
    > link: https://leetcode.com/problems/grumpy-bookstore-owner
    > No: 1052. Grumpy Bookstore Owner
    > Contest: https://leetcode.com/contest/weekly-contest-138/problems/grumpy-bookstore-owner/
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
        int ans = 0;
        int tmpAns = 0;

        for(int i=0;i<grumpy.size();i++){
            grumpy[i] = !grumpy[i];
        }

        for(int i=0;i<X;i++){
            tmpAns += customers[i];
        }
        for(int i=X;i<customers.size();i++){
            tmpAns += grumpy[i] * customers[i];
        }

        ans = tmpAns;

        for(int i=X;i < customers.size(); i++){
            tmpAns -= customers[i-X];
            tmpAns += grumpy[i-X] * customers[i-X];

            tmpAns -= grumpy[i] * customers[i];
            tmpAns += customers[i];
            ans = max(ans, tmpAns);
        }
        return ans;
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
