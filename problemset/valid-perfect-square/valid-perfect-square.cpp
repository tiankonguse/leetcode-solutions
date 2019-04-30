/*************************************************************************
    > File Name: valid-perfect-square.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat Apr 27 22:30:48 2019
    > link: https://leetcode.com/problems/valid-perfect-square/
    > No: 367. Valid Perfect Square
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    bool isPerfectSquare(int num) {
        long long left = 1, right = num,mid;
        while(left <= right){
            mid = (left + right)/2;
            long long midEx = mid * mid;
            if(midEx == num){
                return true;
            }
            if(midEx > num){
                right = mid - 1;
            }else{
                left = mid + 1;
            }
        }
        return false;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
*/
int main() {
    #define CLASS Solution
    #define FUNCTION isPerfectSquare

    int first;
    bool expectAns;

    first = 16;
    expectAns = true;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = 14;
    expectAns = false;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    return 0;
}
