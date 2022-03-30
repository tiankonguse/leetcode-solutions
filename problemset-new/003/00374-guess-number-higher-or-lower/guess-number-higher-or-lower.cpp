/*************************************************************************
    > File Name: guess-number-higher-or-lower.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat Apr 27 00:02:00 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

int pick;
int guess(int num){
    if(pick > num){
        return 1;
    }else if(pick < num){
        return -1;
    }else{
        return 0;
    }
}

class Solution {
public:
    int guessNumber(int n) {
        long long left = 0, right = n, mid;
        int ret;
        while(1){
            mid = (left + right)/2;
            ret = guess(mid);
            if(ret == 0){
                return mid;
            }else if(ret < 0){
                right = mid - 1;
            }else{
                left = mid + 1;
            }
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
    #define FUNCTION guessNumber

    int first;
    int second;
    int expectAns;

    first = 10;
    pick  = 6;
    expectAns = 6;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    return 0;
}
