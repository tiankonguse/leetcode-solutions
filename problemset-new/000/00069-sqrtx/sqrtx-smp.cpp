/*************************************************************************
    > File Name: sqrtx-smp.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri Apr 26 23:49:20 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int mySqrt(int x) {
        if(x<=0)return 0;
        long long left = 0, right = x, mid;
        long long tmp;
        while(left < right){
            mid = (left + right)/2;
            tmp = mid * mid;
            if(tmp == x){
                return mid;
            }
            if(tmp < x){
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
        tmp = left * left;
        if(tmp <= x){
            return left;
        }else{
            return left - 1;
        }
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});

    #define CLASS Solution
    #define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;


    first = 1;
    second = 1;
    expectAns = 1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);
*/
int main() {
    #define CLASS Solution
    #define FUNCTION mySqrt

    int first;
    int second;
    int expectAns;

    first = 4;
    expectAns = 2;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = 8;
    expectAns = 2;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    return 0;
}
