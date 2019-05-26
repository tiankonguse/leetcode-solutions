/*************************************************************************
    > File Name: 1053-previous-permutation-with-one-swap.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 26 10:08:23 2019
    > link: https://leetcode.com/problems/previous-permutation-with-one-swap
    > No: 1053. Previous Permutation With One Swap
    > Contest: https://leetcode.com/contest/weekly-contest-138/problems/previous-permutation-with-one-swap/
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    vector<int> prevPermOpt1(vector<int>& A) {
        int lastPos = A.size()-1;
        for(;lastPos>0 && A[lastPos] >= A[lastPos-1];lastPos--);
        if(lastPos == 0){
            return A;
        }
        lastPos--;

        int swapPos = A.size()-1;
        for(;A[swapPos]>= A[lastPos];swapPos--);
        swap(A[swapPos], A[lastPos]);
        return A;
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
